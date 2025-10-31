# OS Assignment 3 - Concurrency 

* Authors: Christian Nesci, Nicholas Bologiannis, Trent Morgan
* Group name: Group 61

## Overview - Nicholas

This program implements a parallel merge sort algorithm using the pthread library to sort a randomly-generated array of user specificed size, with a random user specified seed to ensure reproducible test results. It first divides the array into smaller subarrays and creates multiple threads (up to a user specified cutoff level) to sort them concurrently, then merges them back together once sorted. Using a multi-threaded approach allows the program to use multiple CPU cores to achieve at least a 2x performance speedup when compared to single threaded merge sort.


## Manifest - Nicholas

- Makefile: Build configuration file that compiles the source files and links them to create the test-mergesort executable.
- mergesort.c: C file that implements the parallel mergesort algorithm.
- mergesort.h: Header file that defines data strcutures, function prototypes, and global variables for the parallel mergesort implementation.
- test-mergesort.c: C file that tests and benchmarks the parallel mergesort implementation by generating a random array, running the sorting algorithm and then measuring execution time and verifying correctness.
- run_tests.sh: Bash script that runs all the tests documented in the testing section.

## Building the project - Trent

How to build:
1. Change directory to comp2002-os-mergesort in your terminal. 
2. Run `make` to compile the program. This will create the dependencies and object files
mergesort.d, mergesort.o, test-mergesort.d, test-mergesort.o and the executable test-mergesort 
3. Run `make clean` if you want to delete mergesort.d, mergesort.o, test-mergesort.d, test-mergesort.o 
and test-mergesort 

## Features and usage - Trent

Run the executable: `./test-mergesort \<input size\> \<cutoff level\> \<seed\>`

For example: ./test-mergesort 100000000 4 1234

\<input size\>: is the size of the array, containing the numbers to be sorted.

\<cutoff level\>: is how many levels the subarrays will be handled concurrently.

Hence, a higher cuttoff level means a larger amount of threads. 

\<seed\>: is a number used to randomly generate the sorting array numbers.

Alternatively, if you are on a Linux system (including WSL) you may run the bash script `./test.sh` to run the preconfigured test cases outlined in this README.
Note: You may need to make this file executable first: `chmod u+x test.sh`

This program will take the starting array of numbers and create a new thread to handle each
new subarray. This means the ordering computations can be done concurrently, making it faster 
to complete the mergesort than it would to do it purely sequentially. The cuttoff level allows 
you to specify how many of these computations you want to do concurrently, so you can optimise
the tradeoff between the time saved by each thread sorting a subarray and the time to handle
the threads themselves. The seed allows you to automatically generate an array of values. The 
same seed will always produce the same array. 

## Testing - Christian

**Scripted tests**: To reproduce the tests, run the script:
```bash
./run_tests.sh
```

### Testing Methodology
Testing was run on WSL using three different tests:
1. **Performance Test**: Measured the execution time with different cutoffs to evaulate the speedup of threading  
2. **Random Seed Test**: Tested accuracy with random seeds
3. **Scalability Test**: Tested with different array sizes to measure performance scaling

### Performance Test
The main performance tests were run with an array size of n=100,000,000 and seed=1234, testing cutoff levels 0-8

**Commands Run**:
```bash
./test-mergesort 100000000 0 1234
./test-mergesort 100000000 1 1234
./test-mergesort 100000000 2 1234
./test-mergesort 100000000 3 1234
./test-mergesort 100000000 4 1234
./test-mergesort 100000000 5 1234
./test-mergesort 100000000 6 1234
./test-mergesort 100000000 7 1234
./test-mergesort 100000000 8 1234
```

| Cutoff Level | Execution Time | Speedup |
|--------------|----------------|---------|
| 0 (sequential) | 9.98 | 1.00x (baseline) |
| 1 | 5.09 | 1.96x |
| 2 | 2.63 | 3.79x |
| 3 | 1.50 | 6.65x |
| 4 | 1.01 | 9.88x |
| 5 | 0.77 | 12.96x |
| 6 | 0.83 | 12.02x |
| 7 | 0.80 | 12.48x |
| 8 | 0.80 | 12.48x |

**Findings**:
- Above level 1, all cutoff levels achieve the 2x speedup.
- Best performance at cutoff level 5
- Above cutoff 5, additional threads make no improvement and actually see worse performance as the computation of thread management outweighs the performance benefit of using additional threads.

### Random Seed Test
Tested with an array size of n=10,000,000 using random seeds at cutoff level 4:

**Commands Run**:
```bash
./test-mergesort 10000000 4 1234
./test-mergesort 10000000 4 5678
./test-mergesort 10000000 4 1111
./test-mergesort 10000000 4 9999
./test-mergesort 10000000 4 7165
./test-mergesort 10000000 4 6323
./test-mergesort 10000000 4 9583
./test-mergesort 10000000 4 2469
```

| Seed | Result | Execution Time |
|------|--------|----------------|
| 1234 | PASS | 0.13 |
| 5678 | PASS | 0.12 |
| 1111 | PASS | 0.12 |
| 9999 | PASS | 0.12 |
| 7165 | PASS | 0.12 |
| 6323 | PASS | 0.12 |
| 9583 | PASS | 0.12 |
| 2469 | PASS | 0.12 |

All test cases pass the check_if_sorted() verification.

### Scalability Test
Compared sequential (cutoff=0) vs parallel (cutoff=4) performance across different array sizes with seed=1234:

**Commands Run**:
```bash
./test-mergesort 1000 0 1234
./test-mergesort 1000 4 1234
./test-mergesort 100000 0 1234
./test-mergesort 100000 4 1234
./test-mergesort 1000000 0 1234
./test-mergesort 1000000 4 1234
./test-mergesort 10000000 0 1234
./test-mergesort 10000000 4 1234
./test-mergesort 100000000 0 1234
./test-mergesort 100000000 4 1234
```

| Array Size | Sequential Time | Parallel Time | Speedup |
|------------|-----------------|---------------|---------|
| 1,000 | 0.00 | 0.00 | N/A (too small) |
| 100,000 | 0.01 | 0.00 | N/A |
| 1,000,000 | 0.08 | 0.02 | 4.00x |
| 10,000,000 | 0.95 | 0.13 | 7.31x |
| 100,000,000 | 10.07 | 1.02 | 9.87x |

Speedup scales well with array size. Small arrays show minimal benefit due to the threading overhead.

### Excessive threading
Some additional tests not included in the bash script were also run to check for the maximum cutoff:
- Cutoff=10 (1,024 threads): Completes but shows performance degradation (0.10s for 1,000,000)
- Cutoff=12 (4,096 threads): Further degradation observed (0.24s for n=1,000,000)
- Cutoff=14 (16,384 threads): **Thread starvation** - system unable to handle the excessive number of threads

## Known Bugs

No bugs observed at time of submission.

## Reflection and Self Assessment - Christian
- The assignment went quite smoothly and we didn't run into many challenges when coding it.
- Something I did run into when testing however, was that our program would fail at a cutoff of 14 and above. I initially though that this was a problem with how we had implemented it, but it is simply due to to a thread starvation error. At a cutoff of 14 the program attempts to use 16,384 threads, which is excessive and adds far too much overhead. So this is not a problem with our implementation, just something that can not be avoided due to the overhead caused by threading.

Overall this assignment was quite enjoyable, and the testing process proved to be quite interesting as we were able to directly see the performance benefits you can obtain from parralelisation.

## Sources Used

- HackerRank 2016, Algorithms: Merge Sort, Youtube, 28th September, viewed October 28 2025, <https://www.youtube.com/watch?v=KF2j-9iSf4Q&t=372s>
