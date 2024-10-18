#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 100;
    int array[N];
    int sum_without_reduction = 0;
    int sum_with_reduction = 0;
    int max_value = 0;

    // Initialize the array with values 1 to N
    for (i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    // ==========================
    // Parallel region without reduction (prone to race conditions)
    printf("===== Without Reduction Clause =====\n");
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        sum_without_reduction += array[i];  // Race conditions may occur here
    }
    printf("Total sum (without reduction): %d\n", sum_without_reduction);

    // ==========================
    // Parallel region with reduction to avoid race conditions
    printf("\n===== With Reduction Clause =====\n");
    #pragma omp parallel for reduction(+:sum_with_reduction) // (operator : variable)
    // each thread gets its private sum_with_rediction variable
    for (i = 0; i < N; i++) {
        sum_with_reduction += array[i];  // Safe reduction across threads
    }
    // safe total sum into the shared variable
    printf("Total sum (with reduction): %d\n", sum_with_reduction);

    
    // ==========================
    // Reduction clause with max operator
    printf("\n===== With Reduction Clause - max operator example =====\n");
    #pragma omp parallel for reduction(max:max_value) // (operator : variable)
    // each thread gets its private sum_with_rediction variable
    for (i = 0; i < N; i++) {
        if (array[i] > max_value) {
            max_value = array[i];  // Compare each element with the current max_value
        }
    }
    printf("Maximum value (with reduction): %d\n", max_value);  // Should be 100

    return 0;
}
