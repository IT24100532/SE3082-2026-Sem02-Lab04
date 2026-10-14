// Exercise 2: S = sum_{i=1..N} [ i - i^2 + sqrt(2 x (i + 1)) ], N = 10,000,000,
// parallelised with OpenMP; the shared S is protected with an ATOMIC section.
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 10000000L

int main(void) {
    double S = 0.0;
    double tstart = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 1; i <= N; i++) {
        double term = (double)i - (double)i * i + sqrt(2.0 * (i + 1));
        #pragma omp atomic
        S += term;
    }

    double tcalc = omp_get_wtime() - tstart;
    printf("%-9s threads = %2d, S = %.6e, time = %f s\n", "atomic:", omp_get_max_threads(), S, tcalc);
    return 0;
}
