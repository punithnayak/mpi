#include <stdio.h>
#include <mpi.h>

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank % 2 == 0) {
        int fact_result = factorial(rank);
        printf("Process %d: Factorial of %d is %d\n", rank, rank, fact_result);
    } else {
        int fib_result = fibonacci(rank);
        printf("Process %d: Fibonacci number at position %d is %d\n", rank, rank, fib_result);
    }

    MPI_Finalize();
    return 0;
}
