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
  int* auxA = new int[tasksPerProcess];
  int* auxB = new int[tasksPerProcess];
  int* auxC = new int[tasksPerProcess];

  MPI_Scatter(A, tasksPerProcess, MPI_INT, auxA, tasksPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(B, tasksPerProcess, MPI_INT, auxB, tasksPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = 0; i < tasksPerProcess; ++i) {
    auxC[i] = auxA[i] + auxB[i];
  }

  MPI_Gather(auxC, tasksPerProcess, MPI_INT, C, tasksPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

  if (myId == 0) {
    printVector(A, n, "Master");
    printVector(B, n, "Master");
    printVector(C, n, "Master");
  }
	
  delete[] auxA;
  delete[] auxB;
  delete[] auxC;

  MPI_Finalize();
}