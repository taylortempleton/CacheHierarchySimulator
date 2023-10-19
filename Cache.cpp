#include <math.h>
#include <vector>  
#include <iostream>

#include "Cache.h"

    void Cache::setParameters(                
                int addressLength, 
                int cacheBlockSize, 
                int cacheSize, 
                int setAssociativity){
                
        numCacheBlocks_ = cacheSize/cacheBlockSize;
        numCacheSets_ = numCacheBlocks_/setAssociativity;

        offsetWidth_ = (int) log2(cacheBlockSize);
        indexWidth_ = (int) log2(numCacheSets_);    
        blockStructArray_.resize(numCacheSets_);
        
        for (int i = 0; i < numCacheSets_; ++i){
            blockStructArray_[i].resize(setAssociativity);
        }
    }

    void Cache::printCfg(){

            std::cout << "  numCacheBlocks_: " << numCacheBlocks_ << std::endl;
            std::cout << "  numCacheSets_ : " << numCacheSets_  << std::endl;
            std::cout << std::endl;

    }

    int Cache::write(int decodedTag, int decodedIndex, int decodedOffset, int setAssociativity, int addressCounter){
            writeTotal++;
            bool writeHit = false;
            int rep_candidate=0; // Default
            for(int j = 0; j < setAssociativity; j++){
                //if(blockStructArray_[decodedIndex][j].tagField == decodedTag && blockStructArray_[decodedIndex][j].validBit == 0){
                if(blockStructArray_[decodedIndex][j].tagField == decodedTag){
                    std::cout << "(Cache::write) WRITE HIT" << std::endl;
                    writeHits++;
                    writeHit = true;
                    blockStructArray_[decodedIndex][j].lruField=addressCounter;
                    blockStructArray_[decodedIndex][j].validBit=1;
                    blockStructArray_[decodedIndex][j].dirtyBit=1;
                    return 1; // Hit
                }
                
            }

            if(writeHit == false){
                std:: cout << "(Cache::write) WRITE MISS" << std::endl;
                writeMisses++;
                // Find eviction candidate
                int lruVal = blockStructArray_[decodedIndex][0].lruField;
                for(int j=0; j<setAssociativity; j++){
                        if(blockStructArray_[decodedIndex][j].lruField < lruVal){
                            rep_candidate = j;                 
                        }                                           
                    }

                // Check dirty bit, if dirty writeback++, if not, simple overwrite
                for(int j=0; j<=setAssociativity; j++){
                    if(blockStructArray_[rep_candidate][j].dirtyBit == 1){
                        writeBacks++;
                        break;
                    }  
                    // for a read miss, the cpu tag field, and transaction counts are updated, block is considererd not dirty and yes valid
                    blockStructArray_[decodedIndex][rep_candidate].tagField=decodedTag;
                    blockStructArray_[decodedIndex][rep_candidate].validBit=1;
                    blockStructArray_[decodedIndex][rep_candidate].dirtyBit=0;
                    blockStructArray_[decodedIndex][rep_candidate].lruField=addressCounter;
                }
            }
            return 0; // Miss
    }

    int Cache::read(int decodedTag, int decodedIndex, int decodedOffset, int setAssociativity, int addressCounter, int numCacheSets){
            readTotal++;
            bool readHit;
            int rep_candidate=0;
            // loop across ways/blocks, for index
            for(int j = 0; j < setAssociativity; j++){
                // if there is a index + tag match, in way j, increment readHits counter, set readHit to true, ubdate lru field
                if(blockStructArray_[decodedIndex][j].tagField == decodedTag){
                    std::cout << "(Cache::read) READ HIT" << std::endl;
                    readHits++;
                    readHit=true;
                    blockStructArray_[decodedIndex][j].lruField = addressCounter;
                    return 1; // Hit
                    }

            }

            // If no read hit, find replacement victim
            if(readHit == false){
                std:: cout << "(Cache::read) READ MISS" << std::endl;
                readMisses++;
                int lruTag = 0;
                // Find eviction candidate
                for(int j=0; j<setAssociativity; j++){
                    for(int i=0; i < numCacheSets; i++){
                        //std::cout << "readCacheModify[i][j].cacheTagField: " << readCacheModify[i][j].lruField << std::endl;
                        if(blockStructArray_[decodedIndex][j].lruField > lruTag){
                            lruTag = blockStructArray_[decodedIndex][j].lruField;
                            rep_candidate = i;                    
                        }
                    }
                }
                // Check dirty bit, if dirty writeback, if not OK to overwrite
                for(int j=0; j<=setAssociativity; j++){
                    if(blockStructArray_[rep_candidate][j].dirtyBit == 1){
                        writeBacks++;
                        break;
                    }  
                    // for a read miss, the cpu tag field, and transaction counts are updated, block is considererd not dirty and yes valid
                    blockStructArray_[decodedIndex][rep_candidate].tagField=decodedTag;
                    blockStructArray_[decodedIndex][rep_candidate].validBit=1;
                    blockStructArray_[decodedIndex][rep_candidate].dirtyBit=0;
                    blockStructArray_[decodedIndex][rep_candidate].lruField=addressCounter;
                }

            }
        return 0; // Miss
        }
