#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 10;
    
    // Parallel region with if clause (true condition)
    printf("With if condition TRUE (n > 5):\n");
    #pragma omp parallel if(n > 5)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("(n > 5): Thread %d of %d: Executing in parallel region\n", thread_num, total_threads);
    }

    printf("\n");

    // Parallel region with if clause (false condition)
    n = 4; // Now make the condition false
    printf("With if condition FALSE (n <= 5):\n");
    #pragma omp parallel if(n > 5)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("(n <= 5): Thread %d of %d: Executing in parallel region\n", thread_num, total_threads);
    }

    return 0;
}
