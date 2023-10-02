*** Work in progress as of 10/2/2023. ECD 11/1/2023 ***

# Cache Hierarchy Simulator

I am a Raleigh, NC based engineer with semiconductor fabrication experience reskilling for a technical role within a computer-hardware manufacturing or design company.  

Below is a small self-assigned project in support of that effort. All input is much appreciated.  Thank you!

Taylor Templeton
taylor.templeton@gmail.com


## Project Summary

Goal: Build understanding of basic cache hierarchy principles (replacement policies, inclusion, set-associativity, etc.).

Output: Create simulator to estimate performance of various cache configurations, and compare against "6 basic cache optimizations" as specified by Hennessy and Patterson in "Computer Architecture : A Quantitative Approach".

Tools: C/C++

## 6 Basic Optimizations

Taken from Hennessy and Patterson in "Computer Architecture : A Quantitative Approach", appendix B.
1. Larger Block Size to Reduce Miss Rate
2. Larger Caches to Reduce Miss Rate
3. Higher Associativity to Reduce Miss Rate
4. Multilevel Caches to Reduce Miss Penalty
5. Giving Priority to Read Misses over Writes to Reduce Miss Penalty
6. Avoiding Address Translation during Indexing of the Cache to Reduce Hit Time

-----------------

## Instructions

1. cd to appropriate path
   $ cd (filepath)
3. Run 'make' to build the executable and its dependencies
   $  make
4. Run the executable with the 8 required user inputs, as specified by the project spec:
     * In order these inputs are:
     
     *   ./executable blocksize L1cachesize L1set-associativity L2cachesize L2set-associativity ReplacementPolicy InclusionProperty MemoryAccessTraceFilename
   $  ./cache_sim 64 32768 1 0 0 0 0 GCC_short.t

Current simulator output to terminal as of Sept 20 2023:
![](https://github.com/taylortempleton/CacheHierarchySimulator/blob/main/Docs/TerminalOutput_Sept20_2023.png)

Status Notes
*** 9/14/2023: Executable will not run with MCT.t 
