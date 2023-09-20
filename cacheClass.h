#pragma once
#include <iostream>

class cacheClass{
    public:
        
        typedef struct cacheStruct{
            unsigned long long cacheTagField;
            int validBit;
            int dirtyBit;
            int policycounter;
            }cacheStruct;

        void readCache(cacheStruct readCacheModify[][32]);
        void writeCache(cacheStruct writeCacheModify[][32]);
        int cacheRepPolicy(cacheStruct cacheRepPolicyModify[][32]);
        int LRU(cacheStruct cacheLRUModify[][32]);

        // *******   Dont want this hard coded? Should it be part of construction?
        cacheStruct classStruct[1024][32];
        
        // Cache Design
        int cacheSize;
        int setAssociativity;
        int cacheBlockSize;
        int numCacheBlocks;
        int numCacheSets;

        //*** New
        int addressLength = 64; //64-bit bite addressable space given
        int indexWidth=0;
        int offsetWidth=0;
        int tagWidth=0;
        std::string replacementPolicy;


        // Metrics
        int readHits=0;
        int totalReads=0;
        int readMisses=0;
        int writeHits=0;
        int totalWrites=0; 
        int writeMisses=0;
        int writeBacks=0;
        int policyCounter=0;

        int l=1;
        float missRate;
        int totalMemoryTraffic;
        unsigned long long cpuAddress,cpuAddrTagField;
        unsigned long cpuAddrIndex;
        unsigned long cpuAddrOffset;

    private:
        // ?
};