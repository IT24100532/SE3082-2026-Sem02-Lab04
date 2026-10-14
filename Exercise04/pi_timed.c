// Exercise 4: Pi using private, shared and firstprivate, with an atomic update.
// Each thread adds into its own private partial sum, then adds it to the shared sum
// ONCE with an atomic update, so there is no data race and almost no waiting.
// Timing: 10 runs, the first 3 are left out (warm-up), the other 7 are averaged.
// The loop uses schedule(runtime), so OMP_SCHEDULE picks the scheduling (default static).
#include <stdio.h>
#include <omp.h>

#define N 100000000L
#define RUNS 10
#define SKIP 3

int main(void) {
    double step = 1.0 / N;      // read-only input, copied into every thread (firstprivate)
    double pi = 0.0, total_time = 0.0;

    for (int run = 0; run < RUNS; run++) {
        double sum = 0.0;       // shared result
        double x, partial;      // scratch values, one copy per thread (private)
        double tstart = omp_get_wtime();

        #pragma omp parallel private(x, partial) shared(sum) firstprivate(step)
        {
            partial = 0.0;
            #pragma omp for schedule(runtime)
            for (long i = 1; i <= N; i++) {
                x = (i - 0.5) * step;
                partial += 1.0 / (1.0 + x * x);
            }
            #pragma omp atomic
            sum += partial;
        }
        pi = 4.0 * sum * step;

        double t = omp_get_wtime() - tstart;
        if (run >= SKIP)
            total_time += t;
    }

    printf("threads = %2d, pi = %.15f, average time = %f s\n",
           omp_get_max_threads(), pi, total_time / (RUNS - SKIP));
    return 0;
}
