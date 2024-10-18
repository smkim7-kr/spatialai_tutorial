#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int N = 8;

    printf("Before the parallel region\n");

    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        
        printf("Thread %d out of %d: Before for loop\n", thread_num, total_threads);

        // No implicit barrier before for constructs
        #pragma omp for
        for (i = 0; i < N; i++) {
            printf("Thread %d is processing iteration %d\n", thread_num, i);
        }
        // implicit barrier after for constructs

        printf("Thread %d out of %d: After for loop\n", thread_num, total_threads);
    }

    printf("After the parallel region\n");
    return 0;
}
