#!/bin/bash

#PBS -l walltime=00:01:00,nodes=1:ppn=3
#PBS -N 1Archies6
#PBS -q batch

cd $PBS_O_WORKDIR

{ time mpirun --hostfile $PBS_NODEFILE -np 1  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 2  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 3  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 4  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 5  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 6  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 7  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 8  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 9  ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 10 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 11 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 12 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 13 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 14 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 15 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 16 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 17 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 18 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 19 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 20 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 21 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 22 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 23 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 24 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 25 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 26 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 27 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 28 ./int 100000000 ; }  2>> /home/s77203/Tasks/1/data.txt
