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


    omp_set_num_threads(countOfThreads);

    

    if (countOfThreads > 1)
    {
        int countOfLocks = (countOfThreads > 2) ? ((countOfThreads - 2) * 2 + 2) : (countOfThreads);
        omp_lock_t *locks;
        locks = (omp_lock_t*)malloc(sizeof(omp_lock_t) * countOfThreads);
        for (_ = 0; _ < countOfThreads; _++)
        {
            omp_set_lock(locks+_);
        }
    }

    omp_lock_t *locks;
    if (countOfThreads > 1)
    {
        int countOfLocks = (countOfThreads > 2) ? ((countOfThreads - 2) * 2 + 2) : (countOfThreads);
        locks = (omp_lock_t*)malloc(sizeof(omp_lock_t) * countOfLocks);
        /*omp_set_lock(locks);
                    for (_ = 1; _ < countOfThreads; _++)
                    {
                        omp_set_lock(locks+_);
                    }   */
                    printf("2");
                }

    int lenghtOfOneThread = (countOfThreads > 1 ) ? ((countOfShaftLenghtsPieces - 2) / ( countOfThreads - 1 )) : (countOfShaftLenghtsPieces - 2);
    for (_ = 0; _ < countOfTimePieces; _++) 
	{
        #pragma omp parallel
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
        }

		uExchange = u0;
        u0 = u1 ;
        u1 = uExchange;
	}


	
	// Вывод на экран. 
	for (_ = 0; _ < countOfShaftLenghtsPieces; _++) 
    {
		printf("%lf \n", u1[_]);
	}

	free(u0);
	free(u1);

    double end_time = omp_get_wtime();
	printf("time: %lf \n", end_time - start_time);
	
	return 0;
}


/*
omp_lock_t *locks;
    if (countOfThreads > 1)
    {
        int countOfLocks = (countOfThreads > 2) ? ((countOfThreads - 2) * 2 + 2) : (countOfThreads);
        locks = (omp_lock_t*)malloc(sizeof(omp_lock_t) * countOfLocks);
        omp_set_lock(locks);
        for (_ = 1; _ < countOfThreads; _++)
        {
            omp_set_lock(locks+_);
        }  
        printf("2");
    }

switch (countOfThreads)
            {
                case 2:
                {
                    switch(omp_get_thread_num())
                    {
                        case 1:
                        {
                            omp_unset_lock(locks);
                            omp_set_lock(locks + 1);
                        }
                        case 2:
                        {
                            omp_unset_lock(locks + 1);
                            omp_set_lock(locks);
                        }
                        default:
                            break;
                    }
                }
                case 3:
                {
                    switch(omp_get_thread_num())
                    {
                        case 1:
                        {
                            omp_unset_lock(locks);
                            omp_set_lock(locks + 1);
                        }
                        case 2:
                        {
                            omp_unset_lock(locks + 1);
                            omp_set_lock(locks);

                            omp_unset_lock(locks + 2);
                            omp_set_lock(locks + 3);
                        }
                        case 3:
                        {
                            omp_unset_lock(locks + 3);
                            omp_set_lock(locks + 2);
                        }
                        default:
                            break;
                    }
                }
                case 4:
                {
                    switch(omp_get_thread_num())
                    {
                        case 1:
                        {
                            omp_unset_lock(locks);
                            omp_set_lock(locks + 1);
                        }
                        case 2:
                        {
                            omp_unset_lock(locks + 1);
                            omp_set_lock(locks);

                            omp_unset_lock(locks + 2);
                            omp_set_lock(locks + 3);
                        }
                        case 3:
                        {
                            omp_unset_lock(locks + 3);
                            omp_set_lock(locks + 2);

                            omp_unset_lock(locks + 4);
                            omp_set_lock(locks + 5);
                        }
                        case 4:
                        {
                            omp_unset_lock(locks + 5);
                            omp_set_lock(locks + 4);
                        }
                        default:
                            break;
                    }
                }
            }

*/



































