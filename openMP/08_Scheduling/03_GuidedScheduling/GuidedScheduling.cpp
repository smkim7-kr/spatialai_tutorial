#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 20; // larger workload units to show guided schdeuling effect
    int array[N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    // threads are dynamically scheduled
    printf("Guided scheduling with chunk size 5:\n");
    #pragma omp parallel for schedule(guided, 5)
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    // initial chunk size = 2, then smaller chunk size given if workload is left
    printf("\nGuided scheduling with chunk size 2:\n");
    #pragma omp parallel for schedule(guided, 2)
    for (i = 0; i < N; i++) {
        printf("Thread %d: processing element %d\n", omp_get_thread_num(), array[i]);
    }

    return 0;
}
