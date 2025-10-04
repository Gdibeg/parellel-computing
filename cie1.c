#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i*i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}
int main() {
    int n = 20;
    int serial_count = 0, parallel_count = 0;
    double start_time, end_time;
    start_time = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            serial_count++;
        }
    }
    end_time = omp_get_wtime();
    double serial_time = end_time - start_time;
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:parallel_count)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) {
            parallel_count++;
        }
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Serial Count of primes = %d\n", serial_count);
    printf("Parallel Count of primes = %d\n", parallel_count);
    printf("Execution time (serial): %.5f seconds\n", serial_time);
    printf("Execution time (parallel): %.5f seconds\n", parallel_time);
    return 0;
}
