//gcc -fopenmp int_OPENMP_for.c -lm && ./a.out 1000000 3 
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
    double sum = h * (f(0) + f(2)) / 2.0;
    int i = 0;
    omp_set_num_threads(countOfThreads);

    #pragma omp parallel
    {
        #pragma omp for reduction(+:sum)
        for(i = 1; i < N - 1; i++)
        {
            sum += h * f(h*i);
        }
    }
    printf("The answer is %lf \n", sum);
    double end_time = omp_get_wtime();
	printf("time: %lf \n", end_time - start_time);
    return 0;
}
