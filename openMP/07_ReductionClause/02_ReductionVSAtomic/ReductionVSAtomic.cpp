#include <stdio.h>
#include <omp.h>

#define N 1000000  // Large array size to observe time difference

int main() {
    int i;
    double start_time, end_time;
    int array[N];
    long long sum_reduction = 0;
    long long sum_atomic = 0;

    // Initialize the array with values 1 to N
    for (i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    // ==========================
    // Measure time for sum with reduction clause
    start_time = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:sum_reduction)
    for (i = 0; i < N; i++) {
        sum_reduction += array[i];  // Safe reduction across threads
    }

    end_time = omp_get_wtime();
    printf("Total sum (with reduction): %lld\n", sum_reduction);
    printf("Time taken (with reduction): %f seconds\n", end_time - start_time);

    // ==========================
    // Measure time for sum with atomic operation
    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        #pragma omp atomic
        sum_atomic += array[i];  // Safe atomic operation but slower
    }

    end_time = omp_get_wtime();
    printf("Total sum (with atomic): %lld\n", sum_atomic);
    printf("Time taken (with atomic): %f seconds\n", end_time - start_time);

    return 0;
}
