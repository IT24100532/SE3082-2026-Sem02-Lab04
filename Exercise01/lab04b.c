// Exercise 1(b): Pi from Lab 03 Exercise 2, data race fixed with a ATOMIC section.
#include <stdio.h>
#include <omp.h>

#ifndef N
#define N 100000000L
#endif

int main(void) {
    double sum = 0.0;
    double tstart = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 1; i <= N; i++) {
        double x = (i - 0.5) / N;
        double term = 1.0 / (1.0 + x * x);
        #pragma omp atomic
        sum += term;                  // the update of sum is done as one indivisible operation
    }
    double pi = 4.0 * sum / N;

    double tcalc = omp_get_wtime() - tstart;
    printf("atomic:   threads = %2d, pi = %.15f, time = %f s\n", omp_get_max_threads(), pi, tcalc);
    return 0;
}
