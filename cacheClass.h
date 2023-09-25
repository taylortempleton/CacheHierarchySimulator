#pragma once
#include <iostream>
#include <vector>

class cacheClass{
    public:

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
        int readMisses=0;
        int totalReads=0;
        int writeHits=0;
        int writeMisses=0;
        int totalWrites=0; 
        int writeBacks=0;
        int memTransactionCount=0;

        int l=1;
        float missRate;
        int totalMemoryTraffic;
        unsigned long long cpuAddress,cpuAddrTagField;
        unsigned long cpuAddrIndex;
        unsigned long cpuAddrOffset;

        typedef struct cacheStruct{
            unsigned long long cacheTagField;
            int validBit = 0;
            int dirtyBit = 0;
            int leastRecentUsedCounterBit = 0;
            }cacheStruct;

        // Define an array of blocks to be sized as needed
        typedef std::vector < std::vector < cacheStruct >> blockStruct;
        
        // by ref
        void readCache(blockStruct& readCacheModify);
        void writeCache(blockStruct& writeCacheModify);
        int cacheRepPolicy(blockStruct& cacheRepPolicyModify);
        int LRU(blockStruct& cacheLRUModify);
        /*
       // by val - original
        void readCache(blockStruct readCacheModify);
        void writeCache(blockStruct writeCacheModify);
        int cacheRepPolicy(blockStruct cacheRepPolicyModify);
        int LRU(blockStruct cacheLRUModify);
        */
        blockStruct blockStructArray;

        //std::vector < std::vector < std::vector < cacheStruct >>> struct3D;


    private:
        // ?
};