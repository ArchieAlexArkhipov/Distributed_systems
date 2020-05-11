#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

long double f(double x){
	if (x*x > 4)
	{
		printf("x is not in [0;2]");
		return 0;
	}
	else
		return sqrt(4 - x*x);
}

//#define f(x) sqrt(4 - x*x)

int main(int argc, char *argv[]) 
{
    int N = atoi(argv[1]);
    double h = (double)2/N;
    double sum = 0.0;
	double totalSum = h * (f(0) + f(2)) / 2.0;
    int i = 0, j = 0;
    int NumberOfProcesses, ProcessRank;
    MPI_Status Status;
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &NumberOfProcesses); 
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcessRank);
    if (ProcessRank == 0)
	{    

		//process rank is 0
		if(NumberOfProcesses > 1)
		{
			int lenghtOfOneProcces = (N - 2) / (NumberOfProcesses - 1);
			for(j = lenghtOfOneProcces * (NumberOfProcesses - 1) + 1; j < N; j++)
			{
	    		totalSum += h * f(h*j);
				//	printf("Procces rank is %d j  =  %d sum = %lf \n", ProcessRank, j, h*totalSum);
			}

        	double partialAmount = 0.0;
        	for (i=1; i < NumberOfProcesses; i++) 
			{
            	MPI_Recv(&partialAmount, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            	totalSum += partialAmount;
	    		//printf("Sum from procces %d", ProcessRank);
        	}
				
        	printf("The answer is %lf \n", totalSum);
		} 
		else 
		{
			for(j = 1; j < N; j++)
			{
	    		totalSum += h * f(h*j);
				//	printf("Procces rank is %d j  =  %d sum = %lf \n", ProcessRank, j, h*totalSum);
			}	

			printf("The answer is %lf \n", totalSum);
		}


	} 
	else 
	{


		//process rank > 0 
        int lenghtOfOneProcces = (N - 2) / ( NumberOfProcesses - 1 );

		for(i = (ProcessRank - 1) * lenghtOfOneProcces + 1; i < ProcessRank * lenghtOfOneProcces + 1 ; i++)
		{
            sum += h * f(h*i);
	    	//printf("Procces rank is %d i  =  %d sum = %lf \n", ProcessRank, i, h*sum);
    	}

        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);


    }


    MPI_Finalize();
    return 0;
}
