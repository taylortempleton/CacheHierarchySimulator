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

CPUs are fast.  They write or read millions of instructions per second.  Memory, which stores these instructions, needs to be fast to keep up with the CPU.  

But, fast memory near the CPU is expensive.  So architects use a "hierarchy", different types of memory linked together.  A small amount of fast, expensive memory is located near the CPU ("L1"), a larger amount of slower memory is located farther away ("L2"), and a huge amount of cheap, slow memory furthest away ("Main memory").  Data is passed between these "levels", to keep only what the CPU needs next close by, and what is needed later farther away.

How well this hierarhy system works depends on each levels' parameters.  For example, imagine the closest memory (L1 cache) only had room for just one instruction: it would always be full, and the CPU would always be accessing the lower, slower caches.  The L1 would be useless.  

This simulator is a simple learning tool to explore how L1/L2 cache parameters impact performance.  One can pick parameters for an L1/L2 cache, and observe missrate and traffic to main memory (more misses or more main memory accesses = more time waiting on slower memory = fewer instructions processed by the CPU per second).

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

