#include <algorithm>
#include <iostream>
#include <barrier>
#include <thread>
#include <string>
#include <vector>
#include <tuple>

class Convolution {
protected:
  int N, M, K, P, halfK;
  int** matrix, ** conv;

private:
  int getElemInCache(int i, int j, int rowIndex, int** cache, int** endCache = nullptr) {
    if (i < 0) {
      i = 0;
    } else if (i >= N) {
      i = N - 1;
    }
    if (j < 0) {
      j = 0;
    } else if (j >= M) {
      j = M - 1;
    }
    if (i > rowIndex) {
      if (endCache == nullptr) {
        return matrix[i][j];
      } else {
        return endCache[i - rowIndex - 1][j];
      }
    }
    return cache[i - rowIndex + halfK][j];
  }

  int oneConv(int i, int j, int** cache, int** endCache = nullptr) {
    int sum = 0;
    for (int p = 0; p < K; ++p) {
      int idx1 = i - K / 2 + p;
      for (int q = 0; q < K; ++q) {
        int idx2 = j - K / 2 + q;
        sum += conv[p][q] * getElemInCache(idx1, idx2, i, cache, endCache);
      }
    }
    return sum;
  }

  void oneLineConv(int i, int** cache, int** endCache = nullptr) {
    for (int j = 0; j < M; ++j) {
      matrix[i][j] = oneConv(i, j, cache, endCache);
    }
  }

  void copyLine(int* source, int sourceStart, int* dest, int destStart, int length) {
    for (int i = 0; i < length; ++i) {
      dest[destStart + i] = source[sourceStart + i];
    }
  }

  int** initCache(int start) {
    int** cache = new int* [halfK + 1];
    for (int i = 0; i <= halfK; ++i) {
      cache[i] = new int[M];
    }
    for (int i = start - halfK; i < start; ++i) {
      if (i < 0) continue;
      if (i >= N) break;
      copyLine(matrix[i], 0, cache[i - start + halfK + 1], 0, M);
    }
    return cache;
  }

  void deleteCache(int** cache) {
    for (int i = 0; i <= halfK; ++i) {
      delete[] cache[i];
    }
    delete[] cache;
  }

  int** initEndCache(int end) {
    int cacheSize = std::min(halfK, N - end - 1);
    int** cache = new int* [cacheSize];
    for (int i = 0; i < cacheSize; ++i) {
      cache[i] = new int[M];
    }
    for (int i = end + 1; i <= end + halfK; ++i) {
      if (i < 0) continue;
      if (i >= N) break;
      copyLine(matrix[i], 0, cache[i - end - 1], 0, M);
    }
    return cache;
  }

  void deleteEndCache(int** cache, int end) {
    int cacheSize = std::min(halfK, N - end - 1);
    for (int i = 0; i < cacheSize; ++i) {
      delete[] cache[i];
    }
    delete[] cache;
  }

  void shiftCache(int** cache, int lineIdx, int** source, int sourceLength) {
    for (int i = 0; i < halfK; ++i) {
      copyLine(cache[i + 1], 0, cache[i], 0, M);
    }
    if (lineIdx < sourceLength) {
      copyLine(source[lineIdx], 0, cache[halfK], 0, M);
    }
  }

  void shiftCache(int** cache, int lineIdx) {
    shiftCache(cache, lineIdx, matrix, N);
  }

public:
  void manyLinesConv(int start, int end) {
    int** cache = initCache(start);
    for (int i = start; i <= end; ++i) {
      shiftCache(cache, i);
      oneLineConv(i, cache);
    }
    deleteCache(cache);
  }

  void manyLinesConvInParallel(int start, int end, std::barrier<std::__empty_completion>&
 bar) {
    int** cache = initCache(start);
    int** endCache = initEndCache(end);
    int endThreshold = end - halfK + 1;
    bar.arrive_and_wait();
    for (int i = start; i <= end; ++i) {
      shiftCache(cache, i);
      if (i >= endThreshold) {
        oneLineConv(i, cache, endCache);
      } else {
        oneLineConv(i, cache);
      }
    }
    deleteCache(cache);
    deleteEndCache(endCache, end);
  }

public:
  Convolution(int** matrix, int** conv, int N, int M, int K, int P) {
    this->matrix = matrix;
    this->conv = conv;
    this->N = N;
    this->M = M;
    this->K = K;
    this->halfK = K / 2;
    this->P = P;
  }

  virtual int** apply() = 0;
};

class SequentialConvolution : public Convolution {
public:
  SequentialConvolution(int** matrix, int** conv, int N, int M, int K)
    : Convolution(matrix, conv, N, M, K, 1) {}

  int** apply() override {
    manyLinesConv(0, N - 1);
    return matrix;
  }
};

class LinesConvolution : public Convolution {
public:
  LinesConvolution(int** matrix, int** conv, int N, int M, int K, int P)
    : Convolution(matrix, conv, N, M, K, P) {}

  int** apply() override {
    std::vector<std::thread*> threads;
    std::barrier bar(P);
    int linesPerThread = N / P;
    int linesRemaining = N % P;
    for (int i = 0; i < N; i += linesPerThread) {
      int start = i;
      if (linesRemaining > 0) {
        ++i;
        --linesRemaining;
      }
      int end = i + linesPerThread - 1;
      threads.push_back(new std::thread(&LinesConvolution::manyLinesConvInParallel, this, start, end, std::ref(bar)));
    }
    for (auto thread : threads) {
      thread->join();
      delete thread;
    }
    return matrix;
  }
};

std::tuple<int, int, int, int**, int**> readFromFile(std::string filename) {
  FILE* fin = fopen(filename.c_str(), "r");
  int n, m, k;
  fscanf(fin, "%d%d", &n, &m);
  int** matrix = new int* [n];
  for (int i = 0; i < n; i++) {
    matrix[i] = new int[m];
    for (int j = 0; j < m; ++j) {
      fscanf(fin, "%d", matrix[i] + j);
    }
  }
  fscanf(fin, "%d", &k);
  int** conv = new int* [k];
  for (int i = 0; i < k; i++) {
    conv[i] = new int[k];
    for (int j = 0; j < k; ++j) {
      fscanf(fin, "%d", conv[i] + j);
    }
  }
  fclose(fin);
  return { n, m, k, matrix, conv };
}

void writeToFile(std::string filename, int N, int M, int** answer) {
  FILE* fout = fopen(filename.c_str(), "w");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M - 1; ++j) {
		  fprintf(fout, "%d ", answer[i][j]);
		}
    fprintf(fout, "%d\n", answer[i][M - 1]);
	}
	fclose(fout);
}

std::string BASE_DIR = "files/";
std::string INPUT_DIR = BASE_DIR + "inputs/";
std::string OUTPUT_DIR = BASE_DIR + "outputs/";

int main(int argc, char* argv[]) {
  if ((argc - 1) / 2 != 1) {
    std::cout << "Usage: " << argv[0] << " <input file> <sequential/lines> <threads count>" << std::endl;
	  return 1;
  }

  std::string inputFilename = INPUT_DIR + argv[1];
  auto tuple = readFromFile(inputFilename);
  int n = std::get<0>(tuple), m = std::get<1>(tuple), k = std::get<2>(tuple);
  int** matrix = std::get<3>(tuple), **kernel = std::get<4>(tuple);
  std::string outputFilename = OUTPUT_DIR;

  Convolution* conv = nullptr;
  std::string method = argv[2];
  if (method == "sequential") {
	  conv = new SequentialConvolution(matrix, kernel, n, m, k);
    outputFilename += method + "_" + std::to_string(n) + "_" + std::to_string(m) + "_" + std::to_string(k) + ".txt";
	}
  else if (method == "lines") {
    int p = std::stoi(argv[3]);
    conv = new LinesConvolution(matrix, kernel, n, m, k, p);
    outputFilename += method + "_" + std::to_string(n) + "_" + std::to_string(m) + "_" + std::to_string(k) + "_" + std::to_string(p) + ".txt";
  }

  if (conv == nullptr) {
    std::cout << "Error at convolution initialization!\nMethod " << method << " unknown!" << std::endl;
    return 1;
  }
  auto start = std::chrono::high_resolution_clock::now();
  int** answer = conv->apply();
  auto end = std::chrono::high_resolution_clock::now();
  double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
  std::cout << elapsedTimeMs << std::endl;
  writeToFile(outputFilename, n, m, answer);
  delete conv;
  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  for (int i = 0; i < k; i++) {
		delete[] kernel[i];
	}
  delete[] kernel;

    return 0;
}