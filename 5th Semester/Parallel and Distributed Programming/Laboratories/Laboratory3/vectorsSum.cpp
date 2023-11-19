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
    // Master Code
    for (int i = 0; i < n; i++) {
      A[i] = rand() % 10 + 1;
      B[i] = rand() % 10 + 1;
    }
    int tasksPerProcess = n / (numProcs - 1);
    int remainingTasks = n % (numProcs - 1);
    for (int i = 1; i < numProcs; ++i) {
      start = end;
      end = start + tasksPerProcess;
      if (remainingTasks) {
        ++end;
        --remainingTasks;
      }
      printf("[Master]: Processor %d will work on interval [%d, %d]\n", i, start, end);
      MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&A[start], end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&B[start], end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    for (int i = 1; i < numProcs; ++i) {
      MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(&C[start], end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
    }
    printf("[Master]: Received all the processes calculations...\n");
    printVector(A, n, "Master");
    printVector(B, n, "Master");
    printVector(C, n, "Master");
  } else {
    MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&A[start], end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(&B[start], end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    printf("[Processor %d]: I will work on interval [%d, %d]\n", myId, start, end);

    for (int i = start; i < end; i++) {
      C[i] = A[i] + B[i];
    }

    printf("[Processor %d]: Job done!\n", myId);

    MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&C[start], end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

	
  MPI_Finalize();
}