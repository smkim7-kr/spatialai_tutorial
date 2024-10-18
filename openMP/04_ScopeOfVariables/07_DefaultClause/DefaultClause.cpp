#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;  // Shared variable

    // Parallel region with default(none), explicitly specifying the scope
    #pragma omp parallel for default(none) shared(sum)
    for (int i = 0; i < 5; i++) {
        sum += i;  // All threads are modifying the shared variable without synchronization
        printf("Thread %d: i = %d, sum = %d (default shared, no critical region)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (default shared, no critical): %d\n", sum);  // The result might be unpredictable
    return 0;
}
