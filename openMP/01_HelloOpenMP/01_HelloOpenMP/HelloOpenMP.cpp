#include <stdio.h>
#include <stdlib.h>
#include <omp.h>     // OpenMP header


int main() {
    #pragma omp parallel 
    {
        // printf is preferred to std::cout since printf ensures thread-safe locking while printing the whole line
        printf("[Thread %d] Hello OpenMP!\n", omp_get_thread_num());
    }
    return 0;
}
