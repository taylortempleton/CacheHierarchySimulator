# Project #2: Cache Hierarchy Simulator

## Summary
My goal is to build understanding of fundamental cache hierarchy principles (replacement, inclusion, mapping, set-associativity) by completing a cache hierarchy simulator project I found online, from NCSU.  I am not enrolled in this class (ECE521), but thought it was an excellent educational project.

*** 9/14/2023: Executable will not run with MCT.t 

-----------------

Instructions to run the cache hierarchy simulator:

1. Generate cd to appropariate path
   $ cd (filepath)
3. Run 'make' to build the executable and its dependencies
   $  make
4. Run the executable with the 8 required user inputs, as specified by the project spec:
     * In order these inputs are ./executable blocksize L1cachesize L1set-associativity L2cachesize L2set-associativity ReplacementPolicy InclusionProperty MemoryAccessTraceFilename
   $  ./cache_sim 64 32768 1 0 0 0 0 GCC.t

Current simulator output to terminal as of Sept 20 2023:
![](https://github.com/taylortempleton/CacheHierarchySimulator/blob/main/Docs/TerminalOutput_Sept20_2023.png)

All input is much appreciated.  Thank you!

Taylor Templeton
taylor.templeton@gmail.com

I am a Raleigh, NC based engineer with a semiconductor fabrication background reskilling for an entry-level design verification-related engineering role. ([Resume](https://github.com/taylortempleton/VerificationPractice_SimpleCPU/blob/main/Docs/2023_09_Sept_20_TaylorTempleton.pdf))
