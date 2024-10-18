
# Parallel Computing and OpenMP

## Why Parallel Computing

Parallel computing is essential to increase computational speed, manage complex and large-scale tasks, and maximize the usage of modern multi-core and multi-processor architectures. It allows dividing tasks into smaller subtasks to execute simultaneously, enhancing performance and efficiency.

### Key Benefits:
- Speedup in execution time
- Efficient utilization of multi-core processors
- Solves larger computational problems
- Scalability for future technologies

## Introduction to Parallel Computing

Parallel computing involves dividing a problem into smaller subproblems and solving them concurrently across multiple processors or threads.

### Types of Parallelism:
- **Data Parallelism**: Distributes subsets of the same data across multiple threads and performs the same operation on each subset.
- **Task Parallelism**: Different threads perform different tasks on the same or different data.

### Applications:
- Scientific simulations
- Large-scale data processing
- Image and video processing

## Introduction to OpenMP

OpenMP is an API for parallel programming in shared memory systems, widely used in C, C++, and Fortran. It simplifies writing parallel programs by allowing the addition of parallel constructs using compiler directives.

### Basic Components of OpenMP:
- **Directives**: Special pragmas that tell the compiler to parallelize sections of the code.
- **Runtime Library Routines**: Functions that control parallel execution, query thread IDs, etc.
- **Environment Variables**: Used to configure the OpenMP runtime.

### Common Directives:
- `#pragma omp parallel`: Defines a parallel region.
- `#pragma omp for`: Distributes loop iterations among threads.
- `#pragma omp critical`: Protects sections of code to ensure only one thread executes at a time.
- `#pragma omp atomic`: Ensures atomic updates to shared variables.
- `#pragma omp reduction`: Combines the results of multiple threads safely.

### Scheduling in OpenMP:
- **Static Scheduling**: Divides iterations evenly among threads.
- **Dynamic Scheduling**: Assigns chunks of iterations dynamically.
- **Guided Scheduling**: Dynamically assigns chunks, decreasing in size as the loop progresses.

### Reduction Clause:
The reduction clause is used to safely perform operations like summing or multiplying across threads. For example:

```c
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < N; i++) {
    sum += array[i];
}
```

### Guided Scheduling Example:

```c
#pragma omp parallel for schedule(guided, 2)
for (int i = 0; i < N; i++) {
    // Workload here
}
```

OpenMP is essential for making efficient use of modern multi-core processors in a wide range of applications.

### Compiling OpenMP Code:
Example command using `gcc`:
```
gcc −g −Wall −fopenmp −o omp_hello filename.c
```

Example command using `g++`:
```
g++ -g -Wall -fopenmp -o omp_hello filename.cpp
```

