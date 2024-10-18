#include <iostream>
#include <vector>  
#include <omp.h> 

#define VECTOR_SIZE 1024*1024
#define NUM_THREADS 4

int main(void){
    // c is the output vector, where c = a + b
    std::vector<int> a(VECTOR_SIZE, 7);
    std::vector<int> b(VECTOR_SIZE, 5);
    std::vector<int> c(VECTOR_SIZE, 0);

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int tID = omp_get_thread_num();
        // each thread computes 
        // i % NUM_THREADS == tID indexes
        // e.g. thread 1, NUM_THREADS 4 => index 1, 5, 9, 13...
        for (int i = tID ; i < VECTOR_SIZE; i+= NUM_THREADS) 
            c[i] = a[i] + b[i];
    }
    
    int correctoutput = a[0] + b[0];
    bool correctresult = true;
    for (int i = 0; i < VECTOR_SIZE; ++i){
        if (c[i] != correctoutput){
            correctresult = false;
            break;
        }
    }

    printf("The result is %s\n", correctresult?"true":"false");
}
