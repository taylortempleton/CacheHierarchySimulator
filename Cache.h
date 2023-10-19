#pragma once
#include <vector>


    class Cache{
        public:
            int read(int decodedTag, int decodedIndex, int decodedOffset, int setAssociativity, int instructionCounter, int numCacheSets);
            int write(int decodedTag, int decodedIndex, int decodedOffset, int setAssociativity, int instructionCounter);
            void printCfg();
            void setParameters(                
                int addressLength, 
                int cacheBlockSize, 
                int cacheSize, 
                int setAssociativity);

            void resizeCache();

            // Representation of each block
            typedef struct cacheStruct{
                unsigned long long tagField;
                int validBit = 0;
                int dirtyBit = 0;
                int lruField = 0;
            }cacheStruct;
            
            // Array of blocks to be sized as dictated by user inputs defining cache parameters
            typedef std::vector < std::vector < cacheStruct >> blockStruct;

            blockStruct blockStructArray_;

            int offsetWidth_;
            int indexWidth_; 
            int numCacheBlocks_;   
            int numCacheSets_; 

            int readHits = 0;
            int readMisses = 0;
            int writeBacks = 0;
            int writeHits = 0;
            int writeMisses = 0;

            int writeTotal = 0;
            int readTotal = 0;
        
        private:






    };
