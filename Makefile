# Build on Linux (AWS EC2 or Docker): make        Run Exercises 1-3: make run   Exercise 4: make run4
CC = gcc
CFLAGS = -Wall -O2 -fopenmp
THREADS = 1 2 4 8 16

all: bin/lab04a.o bin/lab04b.o bin/sum_critical bin/sum_atomic bin/montecarlo_critical bin/montecarlo_atomic bin/pi_timed

bin/lab04a.o: Exercise01/lab04a.c | bin
	$(CC) $(CFLAGS) $< -o $@
bin/lab04b.o: Exercise01/lab04b.c | bin
	$(CC) $(CFLAGS) $< -o $@
bin/%: Exercise02/%.c | bin
	$(CC) $(CFLAGS) $< -o $@ -lm
bin/%: Exercise03/%.c | bin
	$(CC) $(CFLAGS) $< -o $@
bin/%: Exercise04/%.c | bin
	$(CC) $(CFLAGS) $< -o $@

bin:
	mkdir -p bin

run: all
	@echo "== Exercise 1: Pi"; for t in $(THREADS); do OMP_NUM_THREADS=$$t ./bin/lab04a.o; OMP_NUM_THREADS=$$t ./bin/lab04b.o; done
	@echo "== Exercise 2: S"; for t in $(THREADS); do OMP_NUM_THREADS=$$t ./bin/sum_critical; OMP_NUM_THREADS=$$t ./bin/sum_atomic; done
	@echo "== Exercise 3: Monte Carlo"; for t in $(THREADS); do OMP_NUM_THREADS=$$t ./bin/montecarlo_critical; OMP_NUM_THREADS=$$t ./bin/montecarlo_atomic; done

run4: all
	@echo "== Exercise 4: threads 1-24"; for t in 1 4 8 12 16 20 24; do OMP_NUM_THREADS=$$t OMP_SCHEDULE=static ./bin/pi_timed; done
	@echo "== Exercise 4: schedules at 24 threads"; for s in static static,1 static,1000 dynamic dynamic,1000 guided auto; do printf "%-13s " $$s; OMP_NUM_THREADS=24 OMP_SCHEDULE=$$s ./bin/pi_timed; done

clean:
	rm -rf bin
