#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define MAX_WORD_LENGTH 6

void toggle_word(char* word) {
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32; // Convert lowercase to uppercase
        } else if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] + 32; // Convert uppercase to lowercase
        }
    }
}


int main(int argc, char** argv) {
    int rank, size;
    char word[MAX_WORD_LENGTH]="HElLo";
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        // Sender process
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(word, MAX_WORD_LENGTH, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
        printf("Received toggled word from the receiver: %s\n", word);
    } else if (rank == 1) {
        // Receiver process
        MPI_Recv(word, MAX_WORD_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        toggle_word(word);
       
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
