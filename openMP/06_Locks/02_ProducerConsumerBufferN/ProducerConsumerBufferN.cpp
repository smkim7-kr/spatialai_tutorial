#include <stdio.h>
#include <omp.h>

#define N 5  // Buffer size

int main() {
    int buffer[N];             // Shared buffer of size N
    int in = 0, out = 0;       // Buffer index for producer (in) and consumer (out)
    int count = 0;             // Number of items in the buffer
    omp_lock_t lock;           // Lock for synchronizing access to the buffer

    omp_init_lock(&lock);      // Initialize the lock

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        // Thread 0: Producer
        if (thread_id == 0) {
            for (int i = 0; i < 10; i++) {
                // Wait until there is space in the buffer
                while (count == N) {
                    // Busy wait
                }

                // Acquire the lock to produce data
                omp_set_lock(&lock);
                buffer[in] = i;  // Produce an item
                printf("Producer: Produced %d at index %d\n", i, in);
                in = (in + 1) % N;  // Move the in index in circular buffer fashion
                count++;  // Increase the count of items in the buffer
                omp_unset_lock(&lock);
            }
        }

        // Thread 1: Consumer
        if (thread_id == 1) {
            for (int i = 0; i < 10; i++) {
                // Wait until there is data in the buffer
                while (count == 0) {
                    // Busy wait
                }

                // Acquire the lock to consume data
                omp_set_lock(&lock);
                int item = buffer[out];  // Consume an item
                printf("Consumer: Consumed %d from index %d\n", item, out);
                out = (out + 1) % N;  // Move the out index in circular buffer fashion
                count--;  // Decrease the count of items in the buffer
                omp_unset_lock(&lock);
            }
        }
    }

    omp_destroy_lock(&lock);   // Destroy the lock
    return 0;
}
