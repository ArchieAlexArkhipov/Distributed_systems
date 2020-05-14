//gcc -fopenmp heat_OPENMP_lock.c && ./a.out 0.001 300000000 2 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> 

#define shaftLength 1.0
#define leftSideTemperature 1.0
#define rightSideTemperature 2.0

int main(int argc, char **argv) 
{
    double start_time = omp_get_wtime();
	if (argc != 4) 
	{
		printf("Usage: %s timeOfExperimentInSeconds countOfShaftLenghtsPiecesInMeters countOfThreads\n", argv[0]);
		return 1;
	}

	double timeOfExperiment = atof(argv[1]);
	int countOfShaftLenghtsPieces = atoi(argv[2]);
    int countOfThreads = atoi(argv[3]);

	int  _ = 0;
	double lenghtStride = shaftLength / countOfShaftLenghtsPieces;
	double timeStride = 0.3 * lenghtStride * lenghtStride;
	
	int countOfTimePieces = timeOfExperiment / timeStride;
	
	double *u0 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *u1 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *uExchange = (double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
		
    
	/* Задаем начальные условия. */
	for (_ = 0; _ < countOfShaftLenghtsPieces + 1; _++) 		
	{
		u0[_] = u1[_] = 0.0;
	}

	/* Задаем граничные условия. */
	u0[0] = u1[0] = leftSideTemperature;
	u0[countOfShaftLenghtsPieces] = u1[countOfShaftLenghtsPieces] = rightSideTemperature;

    /*omp_lock_t *locks;
    if (countOfThreads > 1)
    {
        int countLock = 0;
        int countOfLocks = 4;//(countOfThreads > 2) ? ((countOfThreads - 2) * 2 + 2) : (countOfThreads);
        locks = (omp_lock_t*)malloc(sizeof(omp_lock_t) * countOfLocks);
        for(_ = 0; _ < countOfThreads; _++)
            omp_init_lock(locks+_);
        //omp_set_lock(locks);
    }*/
    omp_lock_t _if, barrier, count_lock;
    omp_init_lock(&count_lock);
    omp_init_lock(&_if);
    omp_init_lock(&barrier);
    int count = 1;
    int __if = 1;
    omp_set_num_threads(countOfThreads);

    int lenghtOfOneThread = (countOfThreads > 1 ) ? ((countOfShaftLenghtsPieces - 2) / ( countOfThreads - 1 )) : (countOfShaftLenghtsPieces - 2);
    #pragma omp parallel
    {     
        int t;     
        for (t = 0; t < countOfTimePieces; t++) 
        {
            int i = 0, j = 0;
            if (omp_get_thread_num() == 0)
            {    
                //process rank is 0
                if(countOfThreads > 1)
                {
                    for(j = lenghtOfOneThread * (countOfThreads - 1) + 1; j < countOfShaftLenghtsPieces; j++)
                    {
                        u1[j] = u0[j] + timeStride / lenghtStride / lenghtStride  * (u0[j-1] - 2.0 * u0[j] + u0[j+1]);
                    }

                } 
                else 
                {
                    //1 thread
                    for(j = 1; j < countOfShaftLenghtsPieces; j++)
                    {
                        u1[j] = u0[j] + timeStride / lenghtStride / lenghtStride  * (u0[j-1] - 2.0 * u0[j] + u0[j+1]);
                    }	

                }
            } 
            else 
            {
                //process rank > 0 
                for(i = (omp_get_thread_num() - 1) * lenghtOfOneThread + 1; i < omp_get_thread_num() * lenghtOfOneThread + 1 ; i++)
                {
                    u1[i] = u0[i] + timeStride / lenghtStride / lenghtStride  * (u0[i-1] - 2.0 * u0[i] + u0[i+1]);
                }
            }

            /*if (countOfThreads > 1)
            {
                
                countLock++;
                while(1)
                {
                    if (countLock == countOfThreads)
                    {
                        
                        break;
                    }
                }*/
                
            omp_set_lock(&_if);
            if(__if) {
                __if = 0;
                while(1) {
                    if (count == 1) {
                        break;
                    }
                }
                omp_set_lock(&barrier);
                omp_unset_lock(&_if);
                while(1) {
                    if (count == countOfThreads) {
                        break;
                    }
                }
                __if = 1;
                uExchange = u0;
                u0 = u1 ;
                u1 = uExchange;
                omp_unset_lock(&barrier);
            } else {
                omp_unset_lock(&_if);
                omp_set_lock(&count_lock);
                count++;
                omp_unset_lock(&count_lock);
                omp_set_lock(&barrier);
                omp_set_lock(&count_lock);
                count--;
                omp_unset_lock(&count_lock);
                omp_unset_lock(&barrier);
            }
                
                
        }
    }
    

	
	/* Вывод на экран. 
	for (_ = 0; _ < countOfShaftLenghtsPieces; _++) 
    {
		printf("%lf \n", u1[_]);
	}*/

	free(u0);
	free(u1);

    double end_time = omp_get_wtime();
	printf("time: %lf \n", end_time - start_time);
	
	return 0;
}









