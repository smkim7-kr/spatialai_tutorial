# OpenMP (omp) tutorial
### Based on https://github.com/bluekds/OpenMP-Programming

| File                | tl;dr                                                 |
|---------------------|-----------------------------------------------------------------|
| [01_HelloOpenMP](./01_HelloOpenMP)        | Hello world for OpenMP</br>```#pragma omp parallel ```                        |
| [02_ParallelConstruct](./02_ParallelConstruct)             | Parallel threads execution based on condition</br>```#pragma omp parallel if(n > 5) num_threads(NUM_THREADS)```                                     |
| [03_WorkSharingConstructs](./03_WorkSharingConstructs)              | Define parallel region based oon loop, section, single, nowait clause</br>```#pragma omp parallel for ```                             |
| [04_ScopeOfVariables](./04_ScopeOfVariables)              | Variables declared out/in parallel region is shared/private; Scope types include shared, private, lastprivate, firstprivate</br>```int sum = 0; #pragma omp parallel for private(sum)```                             |
| [05_Synchronization](./05_Synchronization)              | Can ensure synchronization through barrier, critical, automic, master clause</br>```#pragma omp critical```                             |
| [06_Locks](./06_Locks)              | Acquire/Release ownership through OpenMP lock to prevent race conditions</br>```omp_lock_t lock;  omp_init_lock(&lock); omp_set_lock(&lock); omp_unset_lock(&lock);```                             |
| [07_ReductionClause](./07_ReductionClause)              | Reduction operators are faster than atomic operations; it supports basic operators</br>```#pragma omp parallel for reduction(+:sum_var) ```                             |
| [08_Scheduling](./08_Scheduling)              | Can explicitly take scheduling strategy between threads; Methods include static, dynamic, and guided</br>```#pragma omp parallel for schedule(guided, 5) ```                             |
| [09_NestedParallelism](./09_NestedParallelism)              | Can execute parallel region inside parallel region</br>```omp_set_nested(1); #pragma omp parallel { #pragma omp parallel { } }```                             |