#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0; // Ignored by each thread (as it's private)

    #pragma omp parallel for private(sum) num_threads(4)
    for (int i = 0; i < 5; i++) {
        sum = i;  // Each thread gets its own copy of sum, variable should be defined explicitly
        printf("Thread %d: i = %d, sum = %d (private)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (private): %d\n", sum);  // Original sum remains unchanged (sum = 0)
    return 0;
}
