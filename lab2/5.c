#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int message = 42;
        printf("Process %d sending message %d to Process 1\n", rank, message);
        MPI_Ssend(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process %d sent message %d to Process 1\n", rank, message);
        // Deadlock occurs because rank 0 is waiting for the acknowledgment from rank 1, but rank 1 is also waiting to send the message to rank 0.
    } else if (rank == 1) {
        int message = 73;
        printf("Process %d sending message %d to Process 0\n", rank, message);
        MPI_Ssend(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent message %d to Process 0\n", rank, message);
        // Deadlock occurs because rank 1 is waiting for the acknowledgment from rank 0, but rank 0 is also waiting to send the message to rank 1.
    }

    MPI_Finalize();
    return 0;
}
