#include <iostream>
#include <string>
#include <mpi.h> 

using namespace std;

void printVector(int v[], int n, string name) {
  string str = "[" + name + "]: ";
  for (int i = 0; i < n - 1; i++) {
    str += to_string(v[i]) + " ";
  }
  str += to_string(v[n - 1]);
  cout << str << endl;
}

int main(int argc, char* argv[]) {
	int myId, numProcs;
  const int n = 10;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
  
  int A[n] = {0}, B[n] = {0}, C[n] = {0};
  int start = 0, end = 0;
  int* disp = new int[numProcs];
  int* offset = new int[numProcs];

  MPI_Status status;
  MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

  if (myId == 0) {
    for (int i = 0; i < n; ++i) {
      A[i] = rand() % 10 + 1;
      B[i] = rand() % 10 + 1;
    }
  }

  int tasksPerProcess = n / numProcs;
  int remainingTasks = n % numProcs;

  for (int i = 0; i < numProcs; ++i) {
    end = start + tasksPerProcess;
    if (remainingTasks) {
      ++end;
      --remainingTasks;
    }
    disp[i] = start;
    offset[i] = end - start;
    start = end;
  }


  int* auxA = new int[offset[myId]];
  int* auxB = new int[offset[myId]];
  int* auxC = new int[offset[myId]];

  MPI_Scatterv(A, offset, disp, MPI_INT, auxA, offset[myId], MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatterv(B, offset, disp, MPI_INT, auxB, offset[myId], MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < offset[myId]; ++i) {
    auxC[i] = auxA[i] + auxB[i];
  }

  MPI_Gatherv(auxC, offset[myId], MPI_INT, C, offset, disp, MPI_INT, 0, MPI_COMM_WORLD);

  delete[] auxA;
  delete[] auxB;
  delete[] auxC;
  
  delete[] disp;
  delete[] offset;

  if (myId == 0) {
    printVector(A, n, "Master");
    printVector(B, n, "Master");
    printVector(C, n, "Master");
  }

  MPI_Finalize();
}