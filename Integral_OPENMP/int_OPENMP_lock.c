// gcc -fopenmp int_OPENMP_lock.c -lm && ./a.out 10000000000 1

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h> 


double f(double x)
{
	if (x*x > 4)
	{
		printf("x is not in [0;2]");
		return 0;
	}
	else
    {
		return sqrt(4 - x*x);
    }
}

//#define f(x) sqrt(4 - x*x)

int main(int argc, char *argv[]) 
{
	double start_time = omp_get_wtime();

    int N = atoi(argv[1]);
    int countOfThreads = atoi(argv[2]);
    double h = (double)2/N;
    //printf("The h is %lf \n", h);
    double totalSum = - h * (f(0) + f(2)) / 2;
    //printf("The answer is %lf \n", totalSum);
    int currentThread = 0;
    omp_set_num_threads(countOfThreads);
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel
    {
        double sum = 0.0;
        int i = 0;
        currentThread = omp_get_thread_num(); 
        for(i = currentThread; i < N; i += countOfThreads)
        {
            sum += h * f(h * i) ;
        }
        omp_set_lock(&lock);
        totalSum += sum;
        omp_unset_lock(&lock);
    }
    //printf("The answer is %lf \n", totalSum);
    double end_time = omp_get_wtime();
	printf("time: %lf \n", end_time - start_time);
    return 0;
}





/*
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h> 

double f(double x)
{
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
    double start_time = omp_get_wtime();
    int N = atoi(argv[1]);
    int countOfThreads = atoi(argv[2]);

    double h = (double)2/N;
    double sum = 0.0;
	double totalSum = h * (f(0) + f(2)) / 2.0;

    int i = 0, j = 0;

    omp_set_num_threads(countOfThreads);

    int lenghtOfOneThread = (countOfThreads > 1) ? ((N - 2) / ( countOfThreads - 1 )) : 1;

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
        {    


            //process rank is 0
            if(countOfThreads > 1)
            {
                for(j = lenghtOfOneThread * (countOfThreads - 1) + 1; j < N; j++)
                {
                    #pragma omp critical
                        totalSum += h * f(h*j);
                    	//printf("Procces rank is %d j  =  %d sum = %lf \n", omp_get_thread_num(), j, totalSum);
                }

            } 
            else 
            {
                for(j = 1; j < N; j++)
                {
                    totalSum += h * f(h*j);
                    	//printf("Procces rank is %d j  =  %d sum = %lf \n", omp_get_thread_num(), j, totalSum);
                }	

            }


        } 
        else 
        {


            //process rank > 0 

            for(i = (omp_get_thread_num() - 1) * lenghtOfOneThread + 1; i < omp_get_thread_num() * lenghtOfOneThread + 1 ; i++)
            {
                #pragma omp critical
                    totalSum += h * f(h*i);
                //printf("Procces rank is %d i  =  %d sum = %lf \n", omp_get_thread_num(), i, totalSum);
            }


        }
    }

    printf("The answer is %lf \n", totalSum);
    
    double end_time = omp_get_wtime();
	printf("time: %lf \n", end_time - start_time);
    return 0;
}
*/