// Exercise 3: Monte Carlo Pi (10,000,000 points) with OpenMP; the shared counter is
// protected with an CRITICAL section. Each thread has its own rand_r() seed.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define POINTS 10000000L

int main(void) {
    long inside = 0;
    double tstart = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = 12345 + 1000 * omp_get_thread_num();
        #pragma omp for
        for (long i = 0; i < POINTS; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                #pragma omp critical
                inside++;
            }
        }
    }
    double pi = 4.0 * inside / POINTS;

    double tcalc = omp_get_wtime() - tstart;
    printf("%-9s threads = %2d, pi = %.6f, inside = %ld, time = %f s\n", "critical:",
           omp_get_max_threads(), pi, inside, tcalc);
    return 0;
}
