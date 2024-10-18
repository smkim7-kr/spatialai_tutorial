#include <stdio.h>
#include <omp.h>

int main() {
    int thread_num;

    // Parallel region
    #pragma omp parallel num_threads(4)
    {
        thread_num = omp_get_thread_num();

        // Code executed by every thread
        printf("Thread %d: Executing parallel region\n", thread_num);

        // Single clause: executed by only one thread
        #pragma omp single
        {
            printf("Thread %d: Executing single region (only one thread does this)\n", thread_num);
        }
        // implicit barrier here

        // After single, all threads continue
        printf("Thread %d: Continuing after the single region\n", thread_num);
    }
     // implicit barrier here

    return 0;
}
