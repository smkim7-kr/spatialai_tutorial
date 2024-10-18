#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 12; // for loop 12 times
    int array[N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    printf("Static scheduling with chunk size 5:\n");
    // thread 0, 1, 2 shares {5, 5, 2} loops 
    #pragma omp parallel for schedule(static, 5) 
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    printf("\nStatic scheduling with chunk size 2:\n");
    // thread 0-5 shares 4 loops each
    #pragma omp parallel for schedule(static, 2) 
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    return 0;
}
