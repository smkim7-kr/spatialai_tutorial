#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0; // Ignored by each thread (as it's private)

    #pragma omp parallel for private(sum)
    for (int i = 0; i < 5; i++) {
        // some compilier will cause error if sum is not defined explicitly inside parallel region
        printf("Thread %d: i = %d, sum = %d (private)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (private): %d\n", sum);  // Original sum remains unchanged
    return 0;
}
