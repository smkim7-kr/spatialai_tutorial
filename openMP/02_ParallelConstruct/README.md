# OpenMP Parallel Constructs


## 1. Parallel Constructs
- **Parallel Region Directive:**
  - The `#pragma omp parallel [clause list]` directive defines a parallel region where a team of threads is created to execute the code within the structured block. 
  - If no work-sharing directive is specified within the parallel region, all threads will execute the same code redundantly.
  - This is the fundamental construct for parallel programming in OpenMP, allowing multiple threads to perform computations concurrently.

- **Fork-Join Model:**
  - OpenMP uses a fork-join model of parallelism. The program starts with a single thread (master thread). When a parallel region is encountered, the master thread forks a specified number of slave threads to execute the code in parallel. 
  - After completing the parallel region, all threads join back to the master thread at an implicit barrier.
  - Example of a parallel region:
  ```c
  #pragma omp parallel
  {
      // All threads execute this code block
      printf("This is thread %d\n", omp_get_thread_num());
  }
  ```

- **Key Functions & Clauses:**
  - `omp_get_num_threads()` returns the total number of threads in the current team.
  - `omp_get_thread_num()` returns the thread ID of the calling thread, which ranges from 0 (master thread) to N-1.
  - These functions are crucial for identifying and managing thread-specific operations within a parallel region.
  - Example: 
  ```c
  #pragma omp parallel num_threads(4)
  {
      int thread_id = omp_get_thread_num();
      int total_threads = omp_get_num_threads();
      printf("Thread %d out of %d\n", thread_id, total_threads);
  }
  ```

- **Example – Vector Sum:**
  - This example demonstrates how to divide a vector sum operation among multiple threads using OpenMP.
  ```c
  int numElePerThread = VECTOR_SIZE / numThreads;
  int *start = new int[numThreads];
  int *end = new int[numThreads];

  for (int tID = 0; tID < numThreads; tID++) {
      start[tID] = numElePerThread * tID;
      end[tID] = numElePerThread * (tID + 1);
      if (tID == numThreads - 1)
          end[numThreads - 1] = VECTOR_SIZE;
  }

  #pragma omp parallel num_threads(numThreads)
  {
      int tID = omp_get_thread_num();
      for (int i = start[tID]; i < end[tID]; i++)
          c[i] = a[i] + b[i];
  }
  ```
  - Here, the vector is divided into chunks, and each thread is responsible for computing the sum for its assigned chunk.

## 2. Work-Sharing Constructs
- **Loop Construct:**
  - The `#pragma omp for [clause list]` directive is used to parallelize loops. Each iteration of the loop is distributed across multiple threads.
  - The loop index variable must be an integer, and the loop control variables (start, end, increment) should not change within the loop.
  - This construct is most commonly used in data-parallel tasks, where the same operation needs to be performed on different pieces of data.
  - Example:
  ```c
  #pragma omp parallel num_threads(4)
  {
      #pragma omp for
      for (int i = 0; i < 16; i++) {
          printf("[Thread %d] executes loop iteration %d\n", omp_get_thread_num(), i);
      }
  }
  ```
  - This loop is divided among four threads, each executing a portion of the loop iterations.

- **Sections Construct:**
  - The `#pragma omp sections` directive is used to divide the workload into sections where each section can be executed by a different thread.
  - This construct is useful when different tasks need to be performed in parallel, rather than performing the same task on different data.
  - Example:
  ```c
  #pragma omp parallel num_threads(8)
  {
      #pragma omp sections
      {
          #pragma omp section
          printf("Section A executed by thread %d\n", omp_get_thread_num());

          #pragma omp section
          printf("Section B executed by thread %d\n", omp_get_thread_num());
      }
  }
  ```
  - Here, different sections of code (tasks) are executed by different threads.

- **Single Construct:**
  - The `#pragma omp single` directive specifies that the enclosed block of code is to be executed by only one thread, chosen non-deterministically.
  - This is typically used for initialization or I/O tasks that should not be duplicated by every thread.
  - Example:
  ```c
  #pragma omp single
  {
      a = 10;
      printf("Single construct executed by thread %d\n", omp_get_thread_num());
  }
  ```

## 3. Scope of Variables
- **Shared and Private Clauses:**
  - The `shared` clause specifies that variables are shared among all threads. All threads can read and write the shared variables.
  - The `private` clause specifies that each thread has its own instance of the variable, and these instances are not shared between threads.
  - Example:
  ```c
  #pragma omp parallel for num_threads(4) shared(re) private(a)
  for (int i = 0; i < 4; i++) {
      a = i;
      a = a*a;
      re[i] = a;
  }
  ```
  - In this example, `a` is private to each thread, meaning each thread has its own copy, while `re` is shared.

- **Lastprivate Clause:**
  - The `lastprivate` clause ensures that the variable holds the value from the last iteration of the loop after the parallel region ends.
  - This is useful when the last value of a variable needs to be preserved after parallel execution.
  - Example:
  ```c
  #pragma omp parallel for num_threads(4) private(tid) lastprivate(priVar)
  for (int i = 0; i < 16; i++) {
      tid = omp_get_thread_num();
      priVar = tid * 10 * i;
      printf("[Thread %d, loop %d] priVar = %d\n", tid, i, priVar);
  }
  printf("[After parallel region] priVar = %d\n", priVar);
  ```

- **Firstprivate Clause:**
  - The `firstprivate` clause initializes private variables with the value they had before entering the parallel region.
  - This is useful when each thread needs to start with the same initial value for a variable but then work on it independently.
  - Example:
  ```c
  #pragma omp parallel for num_threads(4) private(tid) firstprivate(priVar)
  for (int i = 0; i < 4; i++) {
      tid = omp_get_thread_num();
      priVar = priVar * 10 + i;
      printf("[Thread %d] priVar = %d\n", tid, priVar);
  }
  ```

- **Default Clause:**
  - The `default(none)` clause forces the programmer to explicitly specify the data-sharing attributes for each variable in the parallel region. This reduces the risk of unintended sharing or private instances.
  - This clause is recommended for clarity and to avoid errors in parallel programming.
  - Example:
  ```c
  #pragma omp parallel default(none) shared(a) private(b)
  {
      // Code block with explicitly defined variable scope
  }
  ```

This expanded summary provides more details on how each construct and clause operates in OpenMP, with additional context and examples. It serves as a more comprehensive guide to the material covered in the lecture.
