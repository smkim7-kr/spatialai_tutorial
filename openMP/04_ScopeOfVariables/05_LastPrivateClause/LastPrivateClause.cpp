#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0; // Shared, but last iteration's result is copied back

    #pragma omp parallel for lastprivate(sum)
    for (int i = 0; i < 5; i++) {
        sum = i;  // Each thread works with its own sum, but only the last thread's result is used
        printf("Thread %d: i = %d, sum = %d (lastprivate)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (lastprivate): %d\n", sum);  // sum is now the value from the last iteration (i = 4)
    return 0;
}
