#include <stdio.h>
#include <mpi.h>

int main(int argc,char **argv){
	int rank,size;
	MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    int number=69;
    if (rank == 0) {
        // Master process
        for (int dest = 1; dest < size; dest++) {
            number = dest * 10;
            MPI_Send(&number, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        }
    } else {
        // Slave processes
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Slave %d received number: %d\n", rank, number);
    }


    MPI_Finalize();
    return 0;
}
