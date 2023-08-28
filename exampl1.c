#include<stdio.h>
#include<mpi.h>
int main(int argc, char **argv){
	int rank,x;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&x);
	printf("hello world from rank %d",power);
	MPI_Finalize();

	return 0;
}