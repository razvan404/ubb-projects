#include <stdio.h>
#include <stdlib.h> 
#include <mpi.h> 

int main(int argc, char* argv[]) {
	int myid, numprocs, namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(NULL, NULL);

    // get current process id
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    // COMM - communicator, logic instance of the execution we are running
    //      - we are using the global instance of this
	
    // get number of processeser
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Get_processor_name(processor_name, &namelen);

	if (myid == 0) {
        printf("number of processes: %d...\n", numprocs);
    }

    printf("%s: Hello world from process %d \n", processor_name, myid);
	
    MPI_Finalize();
}