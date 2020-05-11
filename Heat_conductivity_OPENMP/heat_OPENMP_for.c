//gcc -fopenmp heat_OPENMP.c && ./mp.out 0.1 100 4 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> 

#define shaftLength 1.0
#define leftSideTemperature 1.0
#define rightSideTemperature 2.0

int main(int argc, char **argv) 
{
	clock_t begin = clock();
	if (argc != 4) 
	{
		printf("Usage: %s timeOfExperimentInSeconds countOfShaftLenghtsPiecesInMeters countOfThreads\n", argv[0]);
		return 1;
	}

	double timeOfExperiment = atof(argv[1]);
	int countOfShaftLenghtsPieces = atoi(argv[2]);
    int countOfThreads = atoi(argv[3]);

	int shift, j, _, beginIterator, endIterator, countOfProcesses, processRank;
	
	double lenghtStride = shaftLength / countOfShaftLenghtsPieces;
	double timeStride = 0.3 * lenghtStride * lenghtStride;
	
	int countOfTimePieces = timeOfExperiment / timeStride;
	
	double *u0 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *u1 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *uExchange = (double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
		
    
	/* Задаем начальные условия. */
	for (j = 0; j < countOfShaftLenghtsPieces + 1; j++) 		
	{
		u0[j] = u1[j] = 0.0;
	}

	/* Задаем граничные условия. */
	u0[0] = u1[0] = leftSideTemperature;
	u0[countOfShaftLenghtsPieces] = u1[countOfShaftLenghtsPieces] = rightSideTemperature;

	omp_set_num_threads(countOfThreads);
	/* Интегрируем по времени. */
	for (_ = 0; _ < countOfTimePieces; _++) 
	{

		#pragma omp parallel for
			for (j = 1; j < countOfShaftLenghtsPieces; j++) 
        	{ 	
            	u1[j] = u0[j] + timeStride / lenghtStride / lenghtStride  * (u0[j-1] - 2.0 * u0[j] + u0[j+1]);
        	}
        
		uExchange = u0;
        u0 = u1 ;
        u1 = uExchange;
	}
	
	/* Вывод на экран. 
	for (j = 0; j < countOfShaftLenghtsPieces; j++) 
    {
		printf("%lf \n", u1[j]);
	}*/

	free(u0);
	free(u1);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%lf \n", time_spent);
	
	return 0;
}
