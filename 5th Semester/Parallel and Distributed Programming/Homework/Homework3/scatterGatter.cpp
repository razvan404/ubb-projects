#include <iostream>
#include <fstream>
#include <string>
#include <mpi.h> 

using namespace std;

int N, M, K, halfK;
int* matrix, **kernel, *cacheTop, *cacheBottom, *auxMat;

int elemAt(int i, int j, int rowIdx, int colIdx, int lastRowIdx) {
  if (i < 0) i = 0;
  if (j < 0) j = 0; else if (j >= M) j = M - 1;

  if (i > rowIdx) {
    if (i > lastRowIdx) return cacheBottom[(i - lastRowIdx - 1) * M + j];
    return auxMat[i * M + j];
  } else {
    return cacheTop[(i - rowIdx + halfK) * M + j];
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
    auxMat[i * M + j] = oneConv(i, j, lastRowIdx);
  }
}

void initTopCache() {
  cacheTop = new int[(halfK + 1) * M];
}

void shiftTopCache(int* newLine, int idx) {
  for (int i = 0; i < idx; ++i) {
    for (int j = 0; j < M; ++j) {
      cacheTop[i * M + j] = cacheTop[(i + 1) * M + j];
    }
  }
  for (int j = 0; j < M; ++j) {
    cacheTop[idx * M + j] = newLine[j];
  }
}

void destroyTopCache() {
  delete[] cacheTop;
}

void initBottomCache() {
  cacheBottom = new int[halfK * M];
}

void destroyBottomCache() {
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
    shiftTopCache(auxMat + i * M, halfK);
    oneLineConv(i, lines - 1);
  }
}

const string INPUT_FILE = "data/input.txt";
const string OUTPUT_FILE = "data/output_sg.txt";

int main(int argc, char* argv[]) {
	int myId, numProcs;
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  if (myId == 0) {
     start = std::chrono::high_resolution_clock::now();
  }

  MPI_Status status;
  MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

  if (myId == 0) {
    // Master Code
    ifstream fin(INPUT_FILE);
    fin >> K;

    start = std::chrono::high_resolution_clock::now();
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
    matrix = new int[N * M];
    for (int i = 0; i < N * M; ++i) {
      fin >> matrix[i];
    }
  } else {
    MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);
    kernel = new int*[K];
    for (int i = 0; i < K; ++i) {
      kernel[i] = new int[K];
      MPI_Bcast(kernel[i], K, MPI_INT, 0, MPI_COMM_WORLD);
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }
  auxMat = new int[(N / numProcs) * M];

  halfK = K / 2;
  int tasksPerProcess = N / numProcs;
  int* dispTop = new int[numProcs], *dispBottom = new int[numProcs];
  int* offsetTop = new int[numProcs], *offsetBottom = new int[numProcs];

  dispTop[0] = 0;
  offsetTop[0] = 0;

  for (int i = 1; i < numProcs; ++i) {
    dispTop[i] = i * M * tasksPerProcess - halfK * M;
    offsetTop[i] = halfK * M;
  }

  for (int i = 0; i < numProcs - 1; ++i) {
    dispBottom[i] = (i + 1) * M * tasksPerProcess;
    offsetBottom[i] = halfK * M;
  }

  dispBottom[numProcs - 1] = N * M - halfK * M;
  offsetBottom[numProcs - 1] = halfK * M;

  initCache();

  
  MPI_Scatterv(matrix, offsetTop, dispTop, MPI_INT, cacheTop + M, offsetTop[myId], MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatterv(matrix, offsetBottom, dispBottom, MPI_INT, cacheBottom, offsetBottom[myId], MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(matrix, tasksPerProcess * M, MPI_INT, auxMat, tasksPerProcess * M, MPI_INT, 0, MPI_COMM_WORLD);
  convAllLines(tasksPerProcess);
  MPI_Gather(auxMat, tasksPerProcess * M, MPI_INT, matrix, tasksPerProcess * M, MPI_INT, 0, MPI_COMM_WORLD);
  
  if (myId == 0) {
    end = std::chrono::high_resolution_clock::now();
  }
  
  destroyCache();

  if (myId == 0) {
    double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << elapsedTimeMs << std::endl;
    ofstream fout(OUTPUT_FILE);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M - 1; ++j) {
        fout << matrix[i * M + j] << " ";
      }
      fout << matrix[(i + 1) * M - 1] << endl;
    }
    fout.close();
  }
	
  MPI_Finalize();
  return 0;
}