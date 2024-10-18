#include <stdio.h>
#include <omp.h>

omp_lock_t write_lock;   // Lock for writers
int read_count = 0;      // Count of active readers
omp_lock_t read_lock;    // Lock to protect access to read_count

void reader(int id) {
    // Acquire lock to update the read_count
    omp_set_lock(&read_lock);
    read_count++;
    if (read_count == 1) {
        omp_set_lock(&write_lock); // First reader locks writers
    }
    omp_unset_lock(&read_lock);    // Release the read_count lock

    // Reading the shared resource (critical section for readers)
    printf("Reader %d is reading...\n", id);

    // Simulate reading delay
    #pragma omp flush
    omp_set_lock(&read_lock);
    read_count--;
    if (read_count == 0) {
        omp_unset_lock(&write_lock); // Last reader unlocks writers
    }
    omp_unset_lock(&read_lock);
}

void writer(int id) {
    // Only one writer can access the shared resource at a time
    omp_set_lock(&write_lock);
    
    // Writing to the shared resource (critical section for writers)
    printf("Writer %d is writing...\n", id);

    // Simulate writing delay
    #pragma omp flush
    omp_unset_lock(&write_lock); // Release the write lock after writing
}

int main() {
    omp_init_lock(&write_lock);   // Initialize the write lock
    omp_init_lock(&read_lock);    // Initialize the read count lock

    // Parallel region for readers and writers
    #pragma omp parallel num_threads(8)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id % 2 == 0) {
            // Even threads are readers
            reader(thread_id);
        } else {
            // Odd threads are writers
            writer(thread_id);
        }
    }

    omp_destroy_lock(&write_lock); // Destroy the write lock
    omp_destroy_lock(&read_lock);  // Destroy the read count lock

    return 0;
}
