*** Work in progress as of 10/19/2023. ECD 11/1/2023 ***

# Cache Hierarchy Simulator

## Hello!

I am a Raleigh, NC based engineer with semiconductor fabrication experience reskilling for a technical role within a computer-hardware manufacturing or design company.  

Below is a small self-assigned project in support of that effort. All input is much appreciated.  Thank you!

Taylor Templeton
taylor.templeton@gmail.com


## Project Summary

Goal: Build understanding of basic cache hierarchy principles (replacement policies, inclusion, set-associativity, etc.).

Output: Create simulator to estimate performance of various cache configurations, and compare against "6 basic cache optimizations" as specified by Hennessy and Patterson in "Computer Architecture : A Quantitative Approach".

Tools: C/C++

## Wait, what does this thing do?

This simulator allows one pick parameters for an L1/L2 cache, and observe missrate and traffic to main memory.  The goal is to observe how selecting different cache parameters affects memory access frequency and consequently, CPU performance (more misses or more main memory accesses = more time waiting on slower memory = fewer instructions per second processed by the CPU).

CPUs are fast.  They write or read millions of instructions per second.  Memory which stores these instructions needs to be fast to keep up.  But, fast memory near the CPU is expensive.  So, architects use a "hierarchy": a small amount of fast, expensive memory near the CPU, a larger amount of slower memory farther away, and a huge amount of cheap memory furthest away.  Data is passed between these "levels", to keep what the CPU needs next as close to the CPU as possible, and to keep what is not needed farther away.

The parameters of each memory level determine how well this hierarhy system works.  For example, if the closest memory (L1 cache) only had room for one instruction, it would always be full and the CPU would always be accessing the lower, slower caches.  By changing L1 and L2 cache parameters, one can see how often the caches "miss" (don't have the needed data) and must access a slower memory to retrieve it (CPU must wait on the slower memory).

## 6 Basic Optimizations

Hennessy and Patterson* identify 6 relationships between cache parameters.   My goal is to test each with this simulator.
1. Larger Block Size to Reduce Miss Rate
2. Larger Caches to Reduce Miss Rate
3. Higher Associativity to Reduce Miss Rate
4. Multilevel Caches to Reduce Miss Penalty
5. Giving Priority to Read Misses over Writes to Reduce Miss Penalty
6. Avoiding Address Translation during Indexing of the Cache to Reduce Hit Time

*Hennessy and Patterson "Computer Architecture : A Quantitative Approach", appendix B.

-----------------

## Instructions

1. cd to appropriate path
   $ cd (filepath)
3. compile
   $   g++ main.cpp Cache.cpp System.cpp -o main
4. Run the executable with the 8 required user inputs, as specified by the project spec:
     * In order these inputs are:
     
     * ./executablename 1(addressLength) 2(cacheBlockSize) 3(L1 cachesize) 4(L1 setassoc) 5(L2 cachesize) 6(L2 cachesize) 7(tracefile name)

$   ./main 12 32 128 2 128 2 Test_12bit.t

Current simulator output to terminal as of Oct 18 2023:
![](https://github.com/taylortempleton/CacheHierarchySimulator/blob/main/Docs/TerminalOutput_Oct18_2023.png)

Status Notes
*** 9/14/2023: Executable will not run with MCT.t 
