#include <iostream>
#include <math.h>      
#include <vector>
//#include <stdlib.h>
//#include <stdio.h>

#include "cacheClass.h"

int main(int argc , char *argv[]){
    setbuf(stdout,NULL);
   
        //Instantiate cache(s)
        cacheClass L1cache;
        cacheClass L2cache;
        // Isnt this construction? Move inside of class? Maybe not specific to L2?
        L1cache.cacheSize=atoi(argv[2]); // or Cache "total data capacity"
        L1cache.cacheBlockSize=atoi(argv[1]);
        L1cache.setAssociativity=atoi(argv[3]);
        L2cache.cacheSize=atoi(argv[4]); // or Cache "total data capacity"
        L2cache.cacheBlockSize=atoi(argv[1]);
        L2cache.setAssociativity=atoi(argv[5]);
        // Cache design parameter calculations based on inputs
        L1cache.numCacheBlocks = L1cache.cacheSize/L1cache.cacheBlockSize;
        L1cache.numCacheSets = L1cache.numCacheBlocks/L1cache.setAssociativity;
        L1cache.offsetWidth = (int) log2(L1cache.cacheBlockSize);
        L1cache.indexWidth = (int) log2(L1cache.numCacheSets);
        L1cache.tagWidth = L1cache.addressLength-L1cache.indexWidth-L1cache.offsetWidth;
        std::string strArg(argv[6]); // Convert char to string
        L1cache.replacementPolicy = strArg;
        // Size blockStruct appropriately
        L1cache.blockStructArray.resize(L1cache.numCacheSets);
        for (int i = 0; i < L1cache.numCacheSets; ++i){
            L1cache.blockStructArray[i].resize(L1cache.setAssociativity);
        }
  
    // Parse Memory Trace File
    char readOrWrite;
    FILE *fp=fopen(argv[8],"r");
        if(fp==NULL){
            std::cout << std::endl;
            std::cout << "*** Memory trace file problem. ****" << std::endl; 
            std::cout << std::endl; 
            std::cout<< "Check the trace file name is correct, and that is it located in the correct directory." << std::endl;
            std::cout << std::endl; 
            exit(1);
        }
    
    fseek(fp,0,SEEK_SET);

    while(1){

        if(feof(fp)){
                break;
            }
        fscanf(fp,"%c %llx\n",&readOrWrite,&L1cache.cpuAddress);
       
        std::cout << "*** Debug (main) ******** fscanf memory trace file parsing *****************" << std::endl;
        std::cout << "*** Debug (main) readOrWrite: " << readOrWrite << std::endl;
        std::cout << "*** Debug (main) L1cache.address:" << std::hex << L1cache.cpuAddress << std::endl;
        
        // Mask provided addresses to acquire tag, index and offset
        L1cache.cpuAddrTagField = (L1cache.cpuAddress & 0xFFFFFFFFE000)>>(L1cache.indexWidth+L1cache.offsetWidth);
        L1cache.cpuAddrIndex=(L1cache.cpuAddress & 0x1FC0)>>(L1cache.offsetWidth);
        L1cache.cpuAddrOffset=(L1cache.cpuAddress & 0x3F);

        std::cout << "*** Debug (main) L1cache.cpuAddrIndex: " << L1cache.cpuAddrIndex << std::endl;
        std::cout << "*** Debug (main) L1cache.cpuAddrTagField: " << L1cache.cpuAddrTagField << std::endl;
        std::cout << "*** Debug (main) L1cache.cpuAddrOffset: " << L1cache.cpuAddrOffset << std::endl;
/*
        L1cache.blockStructArray. = L1cache.cpuAddrIndex;
        L1cache.cpuAddrTagField
        L1cache.blockStructArray
*/
        if(readOrWrite=='r'){
            //L1cache.readCache(L1cache.classStruct);
            L1cache.readCache(L1cache.blockStructArray);
        }
        else if(readOrWrite=='w'){
            //L1cache.writeCache(L1cache.classStruct);
            L1cache.writeCache(L1cache.blockStructArray);
            }
    };
    L1cache.missRate=(float)((
        (float)L1cache.readMisses+
        (float)L1cache.writeMisses)/
        ((float)L1cache.totalReads+
        (float)L1cache.totalWrites));

    L1cache.totalMemoryTraffic=L1cache.readMisses+L1cache.writeMisses+L1cache.writeBacks;

    std:: cout << std::endl;
    std:: cout << "***** Memory Hierarchy Configuration *****" << std::endl;
    std:: cout << "Cache block size: argv[1]: " << argv[1] << std::endl;
    std:: cout << "L1 cache size: argv[2]: " << argv[2] << std::endl;
    std:: cout << "L1 set-associativity: argv[3]: " << argv[3] << std::endl;
    std:: cout << "L2 cache size: argv[4]: " << argv[4] << std::endl;
    std:: cout << "L2 set-associativity: argv[5]: " << argv[5] << std::endl;
    switch (atoi(argv[6])){
            case 0:
                std:: cout << "Replacement Policy: argv[6] :    LRU (0)" << std::endl;
                break;
            case 1:
                std:: cout << "Replacement Policy: argv[6] :    FIFO (1)" << std::endl;
                break;
            default:
                std:: cout << "Replacement Policy: argv[6] :    (Invalid selection)" << std::endl;
                break;
        }
        switch (atoi(argv[7])){
            case 0:
                std:: cout << "Inclusion Property: argv[7] :    Non-Inclusive (0)" << std::endl;
                break;
            case 1:
                std:: cout << "Inclusion Property: argv[7] :    Inclusive (1)" << std::endl;
                break;
            case 2:
                std:: cout << "Inclusion Property: argv[7] :    Exclusive (2)" << std::endl;
                break;
            default:
                std:: cout << "Inclusion Property: argv[7] :    (Invalid selection)" << std::endl;
                break;
        }      
    std:: cout << "Memory Access Trace Filename: argv[8] : " << argv[8] << std::endl;
    std:: cout << std::endl;

    std:: cout << "***** Calcuated Memory Hierarchy Parameters *****" << std::endl;
    std::cout << "L1cache.numCacheBlocks = L1cache.cacheSize/L1cache.cacheBlockSize:" << L1cache.numCacheBlocks << std::endl;
    std::cout << "L1cache.numCacheSets= L1cache.numCacheBlocks/L1cache.setAssociativity: " << L1cache.numCacheSets << std::endl;
    std::cout << "L1cache.offset_width= (int) log2(L1cache.cacheBlockSize): " << L1cache.offsetWidth << std::endl;
    std::cout << "L1cache.index_width= (int) log2(L1cache.numCacheSets): " << L1cache.indexWidth << std::endl;
    std::cout << "L1cache.tag_width= L1cache.addressLength-L1cache.indexWidth-L1cache.offsetWidth: " << L1cache.tagWidth << std::endl;
    std:: cout << std::endl;

    std:: cout << "***** Memory Hierarchy Simulation Results *****" << std::endl;
    std:: cout << std::endl;
    std:: cout << "L1 read hits: " << L1cache.readHits << std::endl;
    std:: cout << "L1 read misses: " << L1cache.readMisses << std::endl;
    std:: cout << "L1 read total: " << L1cache.totalReads << std::endl;
    std:: cout << std::endl;
    std:: cout << "L1 write hits: " << L1cache.writeHits << std::endl;
    std:: cout << "L1 write misses: " << L1cache.writeMisses << std::endl;
    std:: cout << "L1 total writes: " << L1cache.totalWrites << std::endl;
    std:: cout << std::endl;
    std:: cout << "L1 writebacks: " << L1cache.writeBacks << std::endl;
    std:: cout << "L1 miss rate: " << L1cache.missRate << std::endl;

    /*
    std:: cout << "L2 total reads: " << L2cache.totalReads << std::endl;
    std:: cout << "L2 read misses: " << L2cache.readMisses << std::endl;
    std:: cout << "L2 total writes: " << L2cache.totalWrites << std::endl;
    std:: cout << "L2 write misses: " << L2cache.writeMisses << std::endl;
    std:: cout << "L2 miss rate: " << L2cache.missRate << std::endl;
    std:: cout << "L2 writebacks: " << L2cache.writeBacks << std::endl;
    */
    std:: cout << "Total memory traffic: " << L1cache.totalMemoryTraffic << std::endl;
    std:: cout << std::endl;

/*
    std:: cout << "*************** Print Cache Bits **********************" << std::endl;
    std:: cout << "L1cache.setAssociativity: " << L1cache.setAssociativity << std::endl;
    std:: cout << "L1cache.memTransactionCount: " << L1cache.memTransactionCount << std::endl;
    std:: cout << std::endl;

    for(int i = 0;i<=200;i++){
            for(int j=0;j<L1cache.setAssociativity;j++){
                if((L1cache.blockStructArray[i][j].leastRecentUsedCounterBit)){
                std::cout << "L1cache.classStruct["<<i<<"]["<<j<<"]"<< std::endl;
                std::cout << L1cache.blockStructArray[i][j].cacheTagField << std::endl;
                std::cout << L1cache.blockStructArray[i][j].validBit << std::endl;
                std::cout << L1cache.blockStructArray[i][j].dirtyBit << std::endl;
                std::cout << L1cache.blockStructArray[i][j].leastRecentUsedCounterBit << std::endl;
                }
            }
        }
*/
  
    fclose(fp);

    return 0;
}










