#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int value;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



    if (rank == 0) {
        // Root process
        printf("Enter an integer value: ");
        scanf("%d", &value);

        // Send the value to Process 1
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Root process sent %d to Process 1\n", value);

        // Receive the value back from the last process
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Root process received %d back from the last process\n", value);
    } else {
        // Intermediate processes
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d from Process %d\n", rank, value, rank - 1);

        value++; // Increment the value

        // If not the last process, send the value to the next process
        if (rank < size - 1) {
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            printf("Process %d sent %d to Process %d\n", rank, value, rank + 1);
        } else {
            // Last process, send the value back to the root process
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("Last process sent %d back to the root process\n", value);
        }
    }

    MPI_Finalize();
    return 0;
}
