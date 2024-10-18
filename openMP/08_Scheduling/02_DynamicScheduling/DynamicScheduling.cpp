#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 12;
    int array[N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    printf("Dynamic scheduling with chunk size 5:\n");
    // three threads out ot eight avaiable threads shares {5, 5, 2} loops 
    #pragma omp parallel for schedule(dynamic, 5) 
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    printf("\nDynamic scheduling with chunk size 2:\n");
    // six threads out ot eight avaiable threads shares 4 loops each
    #pragma omp parallel for schedule(dynamic, 2) 
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    return 0;
}
