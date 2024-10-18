#include <stdio.h>
#include <omp.h>

// Function that directly modifies the shared variable 'sum'
int complex_operation(int i, int *sum) {
    for (int j = 0; j < 10000; ++j) {
        continue;  // Simulate complex computation
    }
    *sum += i * i + 2 * i;  // Directly modifying 'sum' in a non-atomic way
    return *sum;  // Returning the updated sum
}

int main() {
    int sum = 0;

    // Parallel region where atomic will fail due to complex operation
    printf("===== Attempting to use atomic with complex operation =====\n");
    sum = 0;  // Reset sum
    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        // Trying to use atomic on a complex operation that internally modifies 'sum'
        #pragma omp atomic
        sum += complex_operation(i, &sum);  // Fails because complex_operation modifies sum outside atomic protection
        printf("Thread %d: i = %d, sum = %d (with atomic on complex operation)\n", omp_get_thread_num(), i, sum);
    }
    printf("Final sum (with atomic on complex operation): %d\n", sum); // correct sum is 375, Likely incorrect due to race conditions

    return 0;
}
