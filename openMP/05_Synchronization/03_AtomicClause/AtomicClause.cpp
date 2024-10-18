#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    // Parallel region without atomic clause
    printf("===== Without Atomic Clause =====\n");
    sum = 0; // Reset sum for comparison
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++) {
        sum += i;  // Race condition occurs here
        printf("Thread %d: i = %d, sum = %d (without atomic)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (without atomic): %d\n", sum);

    // Parallel region with atomic clause
    printf("\n===== With Atomic Clause =====\n");
    sum = 0; // Reset sum for comparison
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++) {
        #pragma omp atomic // vs. Critical clause: atomic protects only single memory operations, but more efficient
        sum += i;  // Atomic ensures that this update to sum is safe
        printf("Thread %d: i = %d, sum = %d (with atomic)\n", omp_get_thread_num(), i, sum); // this is not protected
    }

    printf("Final sum (with atomic): %d\n", sum);

    return 0;
}
