#include <stdio.h>
#include <omp.h>

int main() {
    int buffer = -1;           // Shared buffer with size 1
    int full = 0;              // Indicates if the buffer is full (1) or empty (0)
    omp_lock_t lock;           // OpenMP lock to synchronize producer and consumer

    omp_init_lock(&lock);      // Initialize the lock

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        // Thread 0: Producer
        if (thread_id == 0) {
            for (int i = 0; i < 10; i++) {
                // Wait until buffer is empty
                while (full) {
                    // Busy wait
                }

                // Acquire the lock to produce data
                omp_set_lock(&lock);
                buffer = i;    // Produce an item (e.g., i)
                printf("Producer: Produced %d\n", buffer);
                full = 1;      // Mark the buffer as full
                omp_unset_lock(&lock);
            }
        }

        // Thread 1: Consumer
        if (thread_id == 1) {
            for (int i = 0; i < 10; i++) {
                // Wait until buffer is full
                while (!full) {
                    // Busy wait
                }

                // Acquire the lock to consume data
                omp_set_lock(&lock);
                printf("Consumer: Consumed %d\n", buffer);
                full = 0;      // Mark the buffer as empty
                omp_unset_lock(&lock);
            }
        }
    }

    omp_destroy_lock(&lock);   // Destroy the lock
    return 0;
}
