#pragma once
#include <vector>

#include "Cache.h"

class System{
        public:
            void printCfg();
            void decode(unsigned long long cpuAddress, int L1indexWidth, int L1offsetWidth, int L2indexWidth, int L2offsetWidth);
            void printTabulate(
                int addressCounter,
                int L1readHits,
                int L1readMisses, 
                int L1readTotal,
                int L1writeBacks, 
                int L1writeHits, 
                int L1writeMisses, 
                int L1writeTotal,
                int L2readHits, 
                int L2readMisses, 
                int L2readTotal,
                int L2writeBacks, 
                int L2writeHits, 
                int L2writeMisses,
                int L2writeTotal);

            void buildCaches(
                int addressLength, 
                int cacheBlockSize, 
                int L1cacheSize, 
                int L1setAssociativity, 
                int L2cacheSize,
                int L2setAssociativity);

            int addressLength_;
            int cacheBlockSize_; 
            int L1cacheSize_;
            int L1setAssociativity_;
            int L2cacheSize_;
            int L2setAssociativity_;

            int L1decodedTag_;
            int L1decodedIndex_;
            int L1decodedOffset_;

            int L2decodedTag_;
            int L2decodedIndex_;
            int L2decodedOffset_;

        
        private:



    };

