#include <stdio.h>
#include <omp.h>

int main() {
    int i, sum = 0;
    int N = 10;
    
    // Parallel for loop without handling data dependency
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        sum += i; // Data dependency: multiple threads are updating 'sum' simultaneously
    }

    printf("Sum (without handling data dependency): %d\n", sum); // sum should be 55, but prints much smaller value
    
    return 0;
}
