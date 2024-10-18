#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Only the master thread (thread 0) executes this section
        // No implicit barrier here
        #pragma omp master
        {
            printf("Thread %d (Master): Executing in parallel (with master clause)\n", thread_num);
        }
        // No implicit barrier here, so called explicitly
        #pragma omp barrier

        // All threads can execute this section
        printf("Thread %d: Executing in parallel (outside master)\n", thread_num);
    }

    return 0;
}
