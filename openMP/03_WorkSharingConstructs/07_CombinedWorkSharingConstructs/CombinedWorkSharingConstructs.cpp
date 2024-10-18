#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 10;

    // Example 1: Combined parallel for construct
    printf("===== Example 1: Combined parallel for construct =====\n");
    #pragma omp parallel for // Not needed to write seperate lines for # pragma omp parallel # pragma omp for
    for (i = 0; i < N; i++) {
        printf("Thread %d: Processing iteration %d\n", omp_get_thread_num(), i);
    }

    // Example 2: Combined parallel sections construct
    printf("\n===== Example 2: Combined parallel sections construct =====\n");
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread %d: Executing section 1\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Thread %d: Executing section 2\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Thread %d: Executing section 3\n", omp_get_thread_num());
        }
    }

    return 0;
}
