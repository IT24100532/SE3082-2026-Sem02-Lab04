
![lab](/resources/labslogo-2026.png)
## <div align="center">Lab 04</div>

1. Write a serial and parallel program that uses OpenMP solving issues related to Data Races

## Instructions

1. Use your AWS EC2 instance or another linux instance that has openmp to complete the Lab Exercises
2. For timing the perfornance of your solutons use the code snippet given at the end of the lab sheet
3. Calculate the time for running the program serially and calculate seperately the program for running the program in parallel using OpenMP, change the number of threads as follows 1,2,4,8,16 in each instance.
4. Is your parallel solution answer correct, if it is not do you have an idea why this is the case.


## Exercise 1:

Have a look at the Exercise you did in Lab03 for Exercise 2 - Calculating Pi.
![lab](/resources/equation.png)

Can you fix the data race issue using

a) Critical Section</br>
b) Atomic Section</br>


1.	Compile and run your program using the command below
```
gcc -fopenmp lab04a.c -o lab04a.o
./lab04a.o
```
2. Is the answer correct now?
3. Compare the speeds of the original program you wrote in Lab03 with data races happening and when you use a mutex (critical section, atomic section)
4.	Time the serial and the parallel program, do  you notice a difference.
5.	How many cores does your linux machine have?
6.	Use an new EC2 configuration that is higher tryout the program and change the number of threads used (See Lab02), is there a difference when you run the serial program and the parallel program in this higher EC2 configuration.
7.	What is the speedup for both EC2 instances when you change number of threads in this new version of the program
8.	Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS

 
## Exercise 2:

Parallelize the following problem and run it in both EC2 instances and evaluate the performance use mutexes (critical and atomic sections to ensure the correct calculation is performed)
![lab](/resources/q2.png)

1. Like in Exercise 1, compare how your parallel program performs
2.	Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS

## Exercise 3

Parallelize the computation of Pi using the “Monte Carlo method” that you did in Lab03 use mutexes to fix the earlier program

Find the calculation for 10,000,000 times.

1. Like in Exercise 1, compare how your parallel program performs
2.	Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS


Time your parallel Results
Timing can be obtained as follows
```c
double tstart, tcalc
tstart = omp_get_wtime();

 // code to be timed in here

tstop  = omp_get_wtime();

tcalc = tstop - tstart;  // time in milli seconds
```

## Exercise 4

Look at Exercise 1 and modify the program as follows

![lab](/resources/equation.png)

1.	Use private, shared and first private commands when parallelizing</br>
2.	Use the atomic critical section as part of your solution to calculate the correct answer </br>
3.	Get the average timing of running this code making use of 10 runs and leaving out the first 3 samples.</br>
4.	Vary the number of threads used using the environmental parameter from 1 to 24 in intervals of 4. </br>   
e.g., 1,4,8,12,16,20,24</br>
```set OMP_NUM_THREADS=<number of threads to use>```</br>

5.	Plot the graph No of Threads vs Time for the time obtained.</br>
6. Speedup is Time taken for 1 Threads/Time taken for  N Thread, plot No of Threads vs Speed up</br>
7.	Use different scheduling for threads = 24 and time the performance</br>
8. Ensure your instances are stopped when you complete the lab and delete unwanted resources in AWS

![lab](/resources/Picture1.png)

Time your parallel Results
Timing can be obtained as follows
```c
double tstart, tcalc
tstart = omp_get_wtime();

 // code to be timed in here

tstop  = omp_get_wtime();

tcalc = tstop - tstart;  // time in milli seconds
```

## Exercise 5

![lab](/resources/code.png)

1. Implement the code segments given above and get the running time
2. Find out how many times the commented printed statement run
3. Can you justify why the 2nd and 3rd code segments run faster than the 1st code segment

