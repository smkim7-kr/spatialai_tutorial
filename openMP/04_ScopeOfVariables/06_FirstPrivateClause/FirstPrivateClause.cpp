#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 10;  // Initial value of sum

    #pragma omp parallel for firstprivate(sum) // sum is initialized to the value given before parallel region i.e. 10 form line 5
    for (int i = 0; i < 5; i++) {
        sum += i;  // Each thread starts with the initial value of sum (10)
        printf("Thread %d: i = %d, sum = %d (firstprivate)\n", omp_get_thread_num(), i, sum);
    }

    printf("Final sum (firstprivate): %d\n", sum);  // sum remains the original value after the parallel region
    return 0;
}
