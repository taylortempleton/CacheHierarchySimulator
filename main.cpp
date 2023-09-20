#include <iostream>
#include <math.h>      

#include "cacheClass.h"

int main(int argc , char *argv[])
{
    setbuf(stdout,NULL);
   
        //Instantiate cache(s)
        cacheClass L1cache;
        cacheClass L2cache;

        // Isnt this construction? Move inside of class? Maybe not specific to L2?
        L1cache.cacheBlockSize=atoi(argv[1]);
        L1cache.cacheSize=atoi(argv[2]); // or Cache "total data capacity"
        L1cache.setAssociativity=atoi(argv[3]);

        L2cache.cacheBlockSize=atoi(argv[1]);
        L2cache.cacheSize=atoi(argv[4]); // or Cache "total data capacity"
        L2cache.setAssociativity=atoi(argv[5]);
        
        // Cache design parameter calculations based on inputs
        L1cache.numCacheBlocks = L1cache.cacheSize/L1cache.cacheBlockSize;
     //   printf("***Debug (main) L1cache.numBlocks: %x \n", L1cache.numCacheBlocks);
        L1cache.numCacheSets = L1cache.numCacheBlocks/L1cache.setAssociativity;
       // printf("***Debug (main) L1cache.numSets: %x \n", L1cache.numCacheSets);
        L1cache.offsetWidth = (int) log2(L1cache.cacheBlockSize);
        L1cache.indexWidth = (int) log2(L1cache.numCacheSets);
        L1cache.tagWidth = L1cache.addressLength-L1cache.indexWidth-L1cache.offsetWidth;
        printf("***Debug (main) L1cache.offset_width: %x \n", L1cache.offsetWidth);
        printf("***Debug (main) L1cache.index_width: %x \n", L1cache.indexWidth);
        printf("***Debug (main) L1cache.tag_width: %x \n", L1cache.tagWidth);


        std::string strArg(argv[6]); // Convert char to string
        L1cache.replacementPolicy = strArg;

// **** DEBUG 
// **** Move to cache constructor function?
// **** Only valid for direct map? for n-way associativity, there is one tag per set

        // Initialize cache values
        // Loop across rows
        for(int i = 0;i<L1cache.numCacheSets;i++){
            // Loop across columns, depending on associativity
            for(int j=0;j<L1cache.setAssociativity;j++){
                L1cache.classStruct[i][j].cacheTagField = 0;
                L1cache.classStruct[i][j].validBit = 0;
                L1cache.classStruct[i][j].dirtyBit = 0;
                L1cache.classStruct[i][j].policycounter = 0;  // *************************** RENAME
            }
        }

    // Parse Memory Trace File
    char readOrWrite;
    FILE *fp=fopen(argv[8],"r");
    fseek(fp,0,SEEK_SET);
    if(fp==NULL){
            printf("\n Problem with memory trace file\n");
            exit(1);
        }
    while(1){
        if(feof(fp)){
                break;
            }
        fscanf(fp,"%c %llx\n",&readOrWrite,&L1cache.cpuAddress);
        
        printf("***Debug (main) ******** fscanf memory trace file parsing *****************\n");
        printf("***Debug (main) readOrWrite: %c \n", readOrWrite);
        printf("***Debug (main) L1cache.address: %llx \n", L1cache.cpuAddress);

        // Mask provided addresses to acquire tag, index and offset
        L1cache.cpuAddrTagField = (L1cache.cpuAddress & 0xFFFFFFFFE000)>>(L1cache.indexWidth+L1cache.offsetWidth);
        L1cache.cpuAddrIndex=(L1cache.cpuAddress & 0x1FC0)>>(L1cache.offsetWidth);
        L1cache.cpuAddrOffset=(L1cache.cpuAddress & 0x3F);
        if(readOrWrite=='r'){
            L1cache.readCache(L1cache.classStruct);
        }
        else if(readOrWrite=='w'){
            L1cache.writeCache(L1cache.classStruct);
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
    std:: cout << "***** Memory Hierarchy Simulation Results *****" << std::endl;
    std:: cout << "L1 total reads: " << L1cache.totalReads << std::endl;
    std:: cout << "L1 read misses: " << L1cache.readMisses << std::endl;
    std:: cout << "L1 total writes: " << L1cache.totalWrites << std::endl;
    std:: cout << "L1 write misses: " << L1cache.writeMisses << std::endl;
    std:: cout << "L1 miss rate: " << L1cache.missRate << std::endl;
    std:: cout << "L1 writebacks: " << L1cache.writeBacks << std::endl;
    std:: cout << "L2 total reads: " << L2cache.totalReads << std::endl;
    std:: cout << "L2 read misses: " << L2cache.readMisses << std::endl;
    std:: cout << "L2 total writes: " << L2cache.totalWrites << std::endl;
    std:: cout << "L2 write misses: " << L2cache.writeMisses << std::endl;
    std:: cout << "L2 miss rate: " << L2cache.missRate << std::endl;
    std:: cout << "L2 writebacks: " << L2cache.writeBacks << std::endl;
    std:: cout << "Total memory traffic: " << L1cache.totalMemoryTraffic << std::endl;
    std:: cout << std::endl;
  
    fclose(fp);

    return 0;
}










