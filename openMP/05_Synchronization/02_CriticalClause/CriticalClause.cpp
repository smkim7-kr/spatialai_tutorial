// critical region should be used minimally as they are bottlenecks/serialize of parallel operations
#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    // Parallel region without critical section
    printf("===== Without Critical Clause =====\n");
    sum = 0; // Reset sum for comparison
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++) {
        sum += i; // Race condition occurs here
        printf("Thread %d: i = %d, sum = %d (without critical)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (without critical): %d\n", sum);

    // Parallel region with critical section
    printf("\n===== With Critical Clause =====\n");
    sum = 0; // Reset sum for comparison
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++) {
        #pragma omp critical
        {
            sum += i; // Critical section ensures only one thread modifies sum at a time
            printf("Thread %d: i = %d, sum = %d (with critical)\n", omp_get_thread_num(), i, sum);
        }
    }

    printf("Final sum (with critical): %d\n", sum);

    return 0;
}
