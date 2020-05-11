#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define shaftLength 1.0
#define leftSideTemperature 1.0
#define rightSideTemperature 2.0

int main(int argc, char **argv) 
{
	
	if (argc != 3) 
	{
		printf("Usage: %s timeOfExperimentInSeconds countOfShaftLenghtsPiecesInMeters\n", argv[0]);
		return 1;
	}
	
	MPI_Init(&argc, &argv);
	
	double timeOfExperiment = atof(argv[1]);
	
	int countOfShaftLenghtsPieces = atoi(argv[2]);

	int shift, j, _, beginIterator, endIterator, countOfProcesses, processRank;
	
	double lenghtStride = shaftLength / countOfShaftLenghtsPieces;
	double timeStride = 0.3 * lenghtStride * lenghtStride;
	
	int countOfTimePieces = timeOfExperiment / timeStride;
	
	double *u0 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *u1 = 		(double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
	double *uExchange = (double*) malloc(sizeof(double) * (countOfShaftLenghtsPieces + 1));
		
	MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
	MPI_Comm_size(MPI_COMM_WORLD, &countOfProcesses);
    
	/* Задаем начальные условия. */
	for (j = 0; j < countOfShaftLenghtsPieces + 1; j++) 		
	{
		u0[j] = u1[j] = 0.0;
	}

	/* Задаем граничные условия. */
	u0[0] = u1[0] = leftSideTemperature;
	u0[countOfShaftLenghtsPieces] = u1[countOfShaftLenghtsPieces] = rightSideTemperature;


	if (countOfProcesses > 1)
	{
		int mainLenghForOneProcces = (countOfShaftLenghtsPieces - 1) / (countOfProcesses - 1);
		
		int residualLenghForOneProcces = (countOfShaftLenghtsPieces - 1) % (countOfProcesses - 1);

		if (processRank != 0) 
		{
			/*Procces rank isn't 0*/

			if ((processRank - 1) < residualLenghForOneProcces)
			{
				beginIterator = (processRank - 1) * (mainLenghForOneProcces + 1) + 1;
				endIterator = beginIterator + mainLenghForOneProcces + 1;
			}
			else
			{
				beginIterator = (processRank - 1) * mainLenghForOneProcces + 1 + residualLenghForOneProcces;
				endIterator = beginIterator + mainLenghForOneProcces;
			}

			if (processRank == countOfProcesses - 1) 
			{
				endIterator = countOfShaftLenghtsPieces;
			}

			/* Интегрируем по времени. */
			for (_ = 0; _ < countOfTimePieces; _++) 
			{
				
				if ((processRank % 2 == 1) && 
					(processRank != countOfProcesses - 1) && 
					(processRank != 1)) 
				{
					MPI_Send(&u0[endIterator-1], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD);
					MPI_Recv(&u0[endIterator], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

					MPI_Recv(&u0[beginIterator-1], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Send(&u0[beginIterator], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD);
				}	
				else 
				{
					if ((processRank % 2 == 0) && 
						(processRank != countOfProcesses - 1) && 
						(processRank != 1)) 
					{
					MPI_Recv(&u0[beginIterator-1], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Send(&u0[beginIterator], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD);

					MPI_Send(&u0[endIterator-1], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD);
					MPI_Recv(&u0[endIterator], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					}
					else 
					{
						if ((processRank == 1) && 
							(processRank != countOfProcesses - 1)) 
						{
							MPI_Send(&u0[endIterator-1], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD);
							MPI_Recv(&u0[endIterator], 1, MPI_DOUBLE, processRank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
						}
						else
						{ 
							if ((processRank == countOfProcesses - 1) && 
								(processRank != 1)) 
							{
							MPI_Recv(&u0[beginIterator-1], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							MPI_Send(&u0[beginIterator], 1, MPI_DOUBLE, processRank - 1, 0, MPI_COMM_WORLD);
							}
						}
					}
				}
				for (j = beginIterator; j < endIterator; j++) 
				{
					u1[j] = u0[j] + timeStride / lenghtStride / lenghtStride * (u0[j-1] - 2.0 * u0[j] + u0[j+1]);
				}
				
				uExchange = u0;
				u0 = u1;
				u1 = uExchange;
			}

			MPI_Send(u1 + beginIterator, endIterator - beginIterator, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
		else
		{
			/* Сбор данных. */
			/*Procces rank is 0*/
			int i;
			
			for (i = 1; i < countOfProcesses; i++) 
			{
				if ((i-1) < residualLenghForOneProcces)
				{
					beginIterator = (i - 1) * mainLenghForOneProcces + i;
					endIterator = beginIterator + mainLenghForOneProcces + 1;
				}
				else
				{
					beginIterator = (i - 1) * mainLenghForOneProcces + 1 + residualLenghForOneProcces;
					endIterator = beginIterator + mainLenghForOneProcces + 1;
				}

				if (i == countOfProcesses - 1)
				{
					endIterator = countOfShaftLenghtsPieces;
				}
				
				MPI_Recv(u1 + beginIterator, endIterator - beginIterator, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			/* Вывод на экран. */
			for (j = 0; j < countOfShaftLenghtsPieces + 1; j++) 
			{
				printf("%lf\n", u1[j]);
			}
		}
	}
	else
	{
		/* Интегрируем по времени. */
		for (_ = 0; _ < countOfTimePieces; _++) 
		{
			for (j = 1; j < countOfShaftLenghtsPieces; j++) 
			{ 	
				u1[j] = u0[j] + timeStride / lenghtStride / lenghtStride  * (u0[j-1] - 2.0 * u0[j] + u0[j+1]);
			}

			uExchange = u0;
			u0 = u1 ;
			u1 = uExchange;
		}
		
		/* Вывод на экран. */
		for (j = 0; j < countOfShaftLenghtsPieces; j++) {
			printf("%lf \n", u1[j]);
		}

	}
	free(u0);
	free(u1);
	
	MPI_Finalize();
	
	return 0;
}
