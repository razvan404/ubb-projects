#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h> 

using namespace std;

int N, M, K, halfK;
int** matrix, **kernel, **cacheTop, **cacheBottom;

int elemAt(int i, int j, int rowIdx, int colIdx, int lastRowIdx) {
  if (i < 0) i = 0;
  if (j < 0) j = 0; else if (j >= M) j = M - 1;

  if (i > rowIdx) {
    if (i > lastRowIdx) return cacheBottom[i - lastRowIdx - 1][j];
    return matrix[i][j];
  } else {
    return cacheTop[i - rowIdx + halfK][j];
  }
}

int oneConv(int i, int j, int lastRowIdx) {
  int sum = 0;
  for (int p = 0; p < K; ++p) {
    int idx1 = i + p - halfK;
    for (int q = 0; q < K; ++q) {
      int idx2 = j + q - halfK;
      sum += kernel[p][q] * elemAt(idx1, idx2, i, j, lastRowIdx);
    }
  }
  return sum;
}

void oneLineConv(int i, int lastRowIdx) {
  for (int j = 0; j < M; ++j) {
    matrix[i][j] = oneConv(i, j, lastRowIdx);
  }
}

void initTopCache() {
  cacheTop = new int*[halfK + 1];
  for (int i = 0; i <= halfK; ++i) {
    cacheTop[i] = new int[M];
  }
}

void shiftTopCache(int* newLine, int idx) {
  for (int i = 0; i < idx; ++i) {
    for (int j = 0; j < M; ++j) {
      cacheTop[i][j] = cacheTop[i + 1][j];
    }
  }
  for (int j = 0; j < M; ++j) {
    cacheTop[idx][j] = newLine[j];
  }
}

void destroyTopCache() {
  for (int i = 0; i < halfK; ++i) {
    delete[] cacheTop[i];
  }
  delete[] cacheTop;
}

void initBottomCache() {
  cacheBottom = new int*[halfK];
  for (int i = 0; i < halfK; ++i) {
    cacheBottom[i] = new int[M];
  }
}

void destroyBottomCache() {
  for (int i = 0; i < halfK; ++i) {
    delete[] cacheBottom[i];
  }
  delete[] cacheBottom;
}

void initCache() {
  initTopCache();
  initBottomCache();
}

void destroyCache() {
  destroyTopCache();
  destroyBottomCache();
}

void convAllLines(int lines) {
  // Precondition:
  //    the first K / 2 + 1 lines from the previous job are already
  //    in the cacheTop, and the last K / 2 lines from the next job
  //    are already in the cacheBottom.
  for (int i = 0; i < lines; ++i) {
    shiftTopCache(matrix[i], halfK);
    oneLineConv(i, lines - 1);
  }
}

const string INPUT_FILE = "data/input.txt";
const string OUTPUT_FILE = "data/output.txt";

int main(int argc, char* argv[]) {
	int myId, numProcs;

  MPI_Status status;
  MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

  if (myId == 0) {
    // Master Code
    ifstream fin(INPUT_FILE);
    fin >> K;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);
    kernel = new int*[K];
    for (int i = 0; i < K; ++i) {
      kernel[i] = new int[K];
      for (int j = 0; j < K; ++j) {
        fin >> kernel[i][j];
      }
      MPI_Bcast(kernel[i], K, MPI_INT, 0, MPI_COMM_WORLD);
    }
    fin >> N >> M;
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    matrix = new int*[N];

    // Precondition: numProcs - 1 is divisible by N, so no remainder
    int tasksPerProcess = N / (numProcs - 1);

    // The first and the last process will receive only tasksPerProcess + K / 2 lines,
    // the rest of them will receive tasksPerProcess + K lines.
    // The first process:
    for (int i = 0; i < tasksPerProcess + K / 2; ++i) {
      matrix[i] = new int[M];
      for (int j = 0; j < M; ++j) {
        fin >> matrix[i][j];
      }
      MPI_Send(matrix[i], M, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    // The 2 - numProcs - 1 processes:
    for (int k = 2; k < numProcs - 1; ++k) {
      for (int i = tasksPerProcess * (k - 1) - K / 2; i < tasksPerProcess * (k - 1) + K / 2; ++i) {
        MPI_Send(matrix[i], M, MPI_INT, k, 0, MPI_COMM_WORLD);
      }
      for (int i = tasksPerProcess * (k - 1) + K / 2; i < tasksPerProcess * k + K / 2; ++i) {
        matrix[i] = new int[M];
        for (int j = 0; j < M; ++j) {
          fin >> matrix[i][j];
        }
        MPI_Send(matrix[i], M, MPI_INT, k, 0, MPI_COMM_WORLD);
      }
    }
    // The last process:
    for (int i = tasksPerProcess * (numProcs - 2) - K / 2; i < tasksPerProcess * (numProcs - 2) + K / 2; ++i) {
      MPI_Send(matrix[i], M, MPI_INT, numProcs - 1, 0, MPI_COMM_WORLD);
    }
    for (int i = tasksPerProcess * (numProcs - 2) + K / 2; i < N; ++i) {
      matrix[i] = new int[M];
      for (int j = 0; j < M; ++j) {
        fin >> matrix[i][j];
      }
      MPI_Send(matrix[i], M, MPI_INT, numProcs - 1, 0, MPI_COMM_WORLD);
    }
    fin.close();
    
    for (int k = 1; k < numProcs; ++k) {
      for (int i = (k - 1) * tasksPerProcess; i < k * tasksPerProcess; ++i) {
        MPI_Recv(matrix[i], M, MPI_INT, k, 0, MPI_COMM_WORLD, &status);
      }
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << elapsedTimeMs << std::endl;
  

    ofstream fout(OUTPUT_FILE);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M - 1; ++j) {
        fout << matrix[i][j] << " ";
      }
      fout << matrix[i][M - 1] << endl;
    }
    fout.close();
    for (int i = 0; i < K; ++i) {
      delete[] kernel[i];
    }
    delete[] kernel;
    for (int i = 0; i < N; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  else {
    MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);
    halfK = K / 2;
    kernel = new int*[K];
    for (int i = 0; i < K; ++i) {
      kernel[i] = new int[K];
      MPI_Bcast(kernel[i], K, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int tasksPerProcess = N / (numProcs - 1);
    initCache();
    matrix = new int*[tasksPerProcess];
    if (myId != 1) {
      for (int i = 1; i <= halfK; ++i) {
        MPI_Recv(cacheTop[i], M, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      }
    }
    for (int i = 0; i < tasksPerProcess; ++i) {
      matrix[i] = new int[M];
      MPI_Recv(matrix[i], M, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
    if (myId != numProcs - 1) {
      for (int i = 0; i < halfK; ++i) {
        MPI_Recv(cacheBottom[i], M, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      }
    } else {
      for (int i = 0; i < halfK; ++i) {
        for (int j = 0; j < M; ++j) {
          cacheBottom[i][j] = matrix[tasksPerProcess - 1][j];
        }
      }
    }
    convAllLines(tasksPerProcess);
    for (int i = 0; i < tasksPerProcess; ++i) {
      MPI_Send(matrix[i], M, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    for (int i = 0; i < K; ++i) {
      delete[] kernel[i];
    }
    delete[] kernel;
    for (int i = 0; i < tasksPerProcess; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
    destroyCache();
  }
	
  MPI_Finalize();
  return 0;
}