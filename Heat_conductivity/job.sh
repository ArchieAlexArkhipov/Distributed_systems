#!/bin/bash

#PBS -l walltime=00:01:00,nodes=1:ppn=3
#PBS -N 2Archies10100
#PBS -q batch

cd $PBS_O_WORKDIR

{ time mpirun --hostfile $PBS_NODEFILE -np 1  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 2  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 3  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 4  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 5  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 6  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 7  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 8  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 9  ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 10 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 11 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 12 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 13 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 14 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 15 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 16 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 17 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 18 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 19 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 20 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 21 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 22 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 23 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 24 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 25 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 26 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 27 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt
{ time mpirun --hostfile $PBS_NODEFILE -np 28 ./heat 10 100 ; }  2>> /home/s77203/Tasks/2/data.txt

