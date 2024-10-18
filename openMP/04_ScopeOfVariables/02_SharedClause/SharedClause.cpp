#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0; // Shared by all threads

    #pragma omp parallel for shared(sum)
    for (int i = 0; i < 5; i++) {
        sum += i;  // Threads concurrently update shared sum (potential race condition)
        printf("Thread %d: i = %d, sum = %d (shared)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (shared): %d\n", sum);
    return 0;
}
