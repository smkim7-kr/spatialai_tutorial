// implicit barrier exists after parallel & work-sharing constructs (sections, for etc.)
// explicit barrier should be used minimally as they are bottlenecks of parallel operations
#include <stdio.h>
#include <omp.h>

int main() {
    // Parallel region without barrier
    printf("===== Without Barrier =====\n");
    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();

        printf("Thread %d: First section (without barrier)\n", thread_num);

        // No barrier here, threads will not wait for each other
        printf("Thread %d: Seceond section (without barrier)\n", thread_num);
    }

    // Parallel region with barrier
    printf("\n===== With Barrier =====\n");
    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();

        printf("Thread %d: Before the barrier\n", thread_num);

        // Barrier ensures that no thread proceeds until all threads reach this point
        #pragma omp barrier

        printf("Thread %d: After the barrier\n", thread_num);
    }

    return 0;
}
