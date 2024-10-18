#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 10;  // This variable is outside the parallel block and is shared by all threads

    printf("Before parallel region: shared_var = %d\n", shared_var);
    printf("------------------------------------------\n");

    #pragma omp parallel num_threads(4)
    {
        int private_var = omp_get_thread_num();  // This variable is inside the parallel block and is private to each thread

        // Each thread has its own copy of private_var
        printf("Thread %d: Initial private_var = %d\n", omp_get_thread_num(), private_var);

        // Modify the shared variable (all threads access the same shared_var)
        shared_var += omp_get_thread_num();

        // Modify the private variable (each thread has its own copy of private_var)
        private_var += 10;

        // Display values after modification
        printf("Thread %d: Modified private_var = %d, shared_var = %d\n", omp_get_thread_num(), private_var, shared_var);
    }

    // After the parallel region, the shared variable retains the changes made by threads
    printf("------------------------------------------\n");
    printf("After parallel region: shared_var = %d\n", shared_var);

    return 0;
}
