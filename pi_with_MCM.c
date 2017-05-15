#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int N = 10000000;
	int i;
	int ProcNum, ProcRank;
	
	double x,y,S;
	int N_In_Circle;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &ProcNum );
	MPI_Comm_rank( MPI_COMM_WORLD, &ProcRank );
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	N_In_Circle = 0;
	
	for(i = 0; i < N; i++){
		x = ((double)rand())/((double)RAND_MAX);
		y = ((double)rand())/((double)RAND_MAX);
		if (((x*x) + (y*y)) <= 1) N_In_Circle++;
	}
	
	int all_points = 0;
	MPI_Allreduce(&N_In_Circle, &all_points, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	S = (all_points*4)/((double)N*ProcNum);
	
	MPI_Barrier(MPI_COMM_WORLD);

	if (ProcRank == 0) {
		printf("Points: %d\n", N*ProcNum);
		printf("pi simeq %.4f\n", S);
	}

	
	MPI_Finalize();
	return 0;
}
