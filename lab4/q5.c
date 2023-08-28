#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr, n;
    if (rank == 0) {
        printf("Enter n : ");
        scanf("%d", &n);
        arr = (int *)malloc(n * sizeof(int));

        printf("Enter array:\n");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(arr, n, MPI_INT, 0, MPI_COMM_WORLD);
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j += 2) {
            if (j < n - 1 && arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);

        for (int j = 1; j < n - 1; j += 2) {
            if (j < n - 1 && arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("Sorted array : ");
        for (int i = 0; i < n; i++) {
            printf("%d\t", arr[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
}
