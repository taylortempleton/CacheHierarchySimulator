#include "cacheClass.h"
#include <iostream>


void cacheClass::readCache(blockStruct& readCacheModify){
//void cacheClass::readCache(blockStruct readCacheModify){
    std:: cout << "(cacheClass::readCache)" << std::endl;
    std:: cout << "(cacheClass::readCache) cpuAddrIndex:" << cpuAddrIndex << std::endl;
    std:: cout << "(cacheClass::readCache) cpuAddrIndex:" << cpuAddrTagField << std::endl;
    int hitCounter=0;
    int counter2=0;
    int rep_candidate=0;
    totalReads+=1;
    memTransactionCount+=1; // Each time read or write function called, this value is incremented

    // replacementPolicy = 0 for LRU
    if(replacementPolicy.compare("0")==0){
        // loop through blocks for the given cpuAddressIndex
        for(int j=0;j<setAssociativity;j++){
            // Read hit = valid=1 and match with cpuAddress requested

                std::cout << "readCacheModify[cpuAddrIndex][j].validBit: " << readCacheModify[cpuAddrIndex][j].validBit << std::endl;
                std::cout << "readCacheModify[cpuAddrIndex][j].cacheTagField: " << readCacheModify[cpuAddrIndex][j].cacheTagField << std::endl;
                std::cout << "cpuAddrTagField: " << cpuAddrTagField << std::endl;

            if(readCacheModify[cpuAddrIndex][j].validBit==1 && (readCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
                std:: cout << "(cacheClass::readCache - read hit)" << std::endl;
                std:: cout << "(cacheClass::readCache - read hit) readCacheModify[cpuAddrIndex][j].validBit: " << readCacheModify[cpuAddrIndex][j].validBit << std::endl;
                readHits+=1; // Update readHits counts
                hitCounter=1; // Note there is a read hit
                readCacheModify[cpuAddrIndex][j].leastRecentUsedCounterBit=memTransactionCount;  // Update with current transaction count for LRU use
                std:: cout << "(cacheClass::readCache - read hit) memTransactionCount: " << memTransactionCount << std::endl;
            break;
            }
        }

        // Read miss
        // hit counter = 0 if no read hit above, therefore a miss
        if(hitCounter==0){
            std:: cout << "(cacheClass::readCache - read miss)" << std::endl;
            readMisses+=1;
            // Loop through blocks again
            for(int j=0;j<setAssociativity;j++){
                // Check if any block j is not valid.  If not valid, store j as replacement candidadate
                if(readCacheModify[cpuAddrIndex][j].validBit==0){
                    rep_candidate=j;
                    std::cout << "(cacheClass::readCache - read miss) rep_candidate: " << rep_candidate << std::endl;
                    break;
                }
                // If any block withing cpuAddrIndex is valid, increment counter 2.... 
                if(readCacheModify[cpuAddrIndex][j].validBit==1){
                    counter2+=1;
                    std::cout << "(cacheClass::readCache - read miss) rep_candidate: " << rep_candidate << std::endl;
                }
            }

            // if counter2 is = to set associativity, run replacement policy function
            // loop across the cpuAddrIndex, if all blocks are valid (which would mean the sum = set Associativity), then we replace that block?
            if(counter2==setAssociativity){
                rep_candidate=cacheRepPolicy(readCacheModify);
            }

            // if the replacement candidate (j from first loop) is dirty & valid, then count writeback
            if(readCacheModify[cpuAddrIndex][rep_candidate].dirtyBit==1 && readCacheModify[cpuAddrIndex][rep_candidate].validBit==1){
                writeBacks+=1;
            }

            // for a read miss, the cpu tag field, and transaction counts are updated, block is considererd not dirty and yes valid
            readCacheModify[cpuAddrIndex][rep_candidate].cacheTagField==cpuAddrTagField;
            readCacheModify[cpuAddrIndex][rep_candidate].leastRecentUsedCounterBit=memTransactionCount;
            readCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=0;
            readCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
        }


    } 

    //replacementPolicy = 1 for FIFO
    else if(replacementPolicy.compare("1")==0){
        for(int j=0;j<setAssociativity;j++){
            // Read hit
            if(readCacheModify[cpuAddrIndex][j].validBit==1 && (readCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
                readHits+=1;
                hitCounter=1;
                break;
            }
        }
    // Read miss
        if(hitCounter==0){
            readMisses+=1;
            for(int j=0;j<setAssociativity;j++){
                if(readCacheModify[cpuAddrIndex][j].validBit==0){
                    rep_candidate=j;
                    break;
                }
                if(readCacheModify[cpuAddrIndex][j].validBit==1){
                    counter2+=1;
                }
            }
            if(counter2==setAssociativity){
                rep_candidate=cacheRepPolicy(readCacheModify);
            }
            if(readCacheModify[cpuAddrIndex][rep_candidate].dirtyBit==1 && readCacheModify[cpuAddrIndex][rep_candidate].validBit==1){
                writeBacks+=1;
            }
            readCacheModify[cpuAddrIndex][rep_candidate].cacheTagField==cpuAddrTagField;
            readCacheModify[cpuAddrIndex][rep_candidate].leastRecentUsedCounterBit=memTransactionCount;
            readCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=0;
            readCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
        }
    }
}


void cacheClass::writeCache(blockStruct& writeCacheModify){
//void cacheClass::writeCache(blockStruct writeCacheModify){
    std:: cout << "(cacheClass::writeCache)" << std::endl;
    std:: cout << "(cacheClass::writeCache) cpuAddrIndex:" << cpuAddrIndex << std::endl;
    int counter=0;
    int counter2=0;
    int rep_candidate=0;
    totalWrites+=1;
    memTransactionCount+=1;
    //replacementPolicy = 0 for LRU
    if(replacementPolicy.compare("0")==0){
        for(int j=0;j<setAssociativity;j++){
        // Write hit
        
        std::cout << writeCacheModify[cpuAddrIndex][j].validBit << std::endl;
        std::cout << "(cacheClass::writeCache) writeCacheModify[cpuAddrIndex][j].cacheTagField:" << writeCacheModify[cpuAddrIndex][j].cacheTagField << std::endl;
        std::cout << cpuAddrTagField << std::endl;

        //if(writeCacheModify[cpuAddrIndex][j].validBit==0 && (writeCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
        if(writeCacheModify[cpuAddrIndex][j].validBit==0){
            std:: cout << "(cacheClass::writeCache - write hit)" << std::endl;
            writeHits+=1;
            counter=1;
            writeCacheModify[cpuAddrIndex][j].cacheTagField = cpuAddrTagField; // write the value
            writeCacheModify[cpuAddrIndex][j].validBit = 1; // set the new block as valid
            writeCacheModify[cpuAddrIndex][j].leastRecentUsedCounterBit=memTransactionCount;
            writeCacheModify[cpuAddrIndex][j].dirtyBit=1;
            std::cout << "(cacheClass::writeCache - write hit, confirm write) writeCacheModify[cpuAddrIndex][j].cacheTagField:" << writeCacheModify[cpuAddrIndex][j].cacheTagField << std::endl;

            std::cout << "(cacheClass::writeCache - write hit, confirm write) writeCacheModify[cpuAddrIndex][j].cacheTagField:" << writeCacheModify[cpuAddrIndex][j].cacheTagField << std::endl;
            break;
        }
        }
    // Write miss
        if(counter==0){
            std:: cout << "(cacheClass::writeCache - write miss)" << std::endl;
            writeMisses+=1;
            for(int j=0;j<setAssociativity;j++){
                if(writeCacheModify[cpuAddrIndex][j].validBit==0){
                    rep_candidate=j;
                    break;
                }
                else
                    counter2+=1;
                }  
                if(counter2==setAssociativity){
                    rep_candidate=cacheRepPolicy(writeCacheModify);
                }
                if(writeCacheModify[cpuAddrIndex][rep_candidate].dirtyBit==1 && writeCacheModify[cpuAddrIndex][rep_candidate].validBit==1){
                    writeBacks+=1;
                }
                writeCacheModify[cpuAddrIndex][rep_candidate].cacheTagField==cpuAddrTagField;
                writeCacheModify[cpuAddrIndex][rep_candidate].leastRecentUsedCounterBit=memTransactionCount;
                writeCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=1;
                writeCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
        }
    }
    //replacementPolicy = 1 for FIFO
    else if(replacementPolicy.compare("1")==0){
        for(int j=0;j<setAssociativity;j++){
        // Write hit
        if(writeCacheModify[cpuAddrIndex][j].validBit==1 && (writeCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
            writeHits+=1;
            counter=1;
            writeCacheModify[cpuAddrIndex][j].dirtyBit=1;
            break;
            }
        }
        // Write miss
        if(counter==0){
            writeMisses+=1;
            for(int j=0;j<setAssociativity;j++){
                if(writeCacheModify[cpuAddrIndex][j].validBit==0){
                    rep_candidate=j;
                    break;
                }
                else
                    counter2+=1;
            }
            if(counter2==setAssociativity){
                rep_candidate=cacheRepPolicy(writeCacheModify);
            }
            if(writeCacheModify[cpuAddrIndex][rep_candidate].dirtyBit==1 && writeCacheModify[cpuAddrIndex][rep_candidate].validBit==1){
                writeBacks+=1;
            }
            writeCacheModify[cpuAddrIndex][rep_candidate].cacheTagField==cpuAddrTagField;
            writeCacheModify[cpuAddrIndex][rep_candidate].leastRecentUsedCounterBit=memTransactionCount;
            writeCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=1;
            writeCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
        }
    }
}

int cacheClass::cacheRepPolicy(blockStruct& cacheRepPolicyModify){
//int cacheClass::cacheRepPolicy(blockStruct cacheRepPolicyModify){
    std:: cout << "(cacheClass::cacheRepPolicy)" << std::endl;
    int rep_candidate;
    // 0 for lru, 2 for pseudo lru
    if(replacementPolicy.compare("0")==0 || replacementPolicy.compare("2")==0){
        rep_candidate=LRU(cacheRepPolicyModify);
    }
    // 
    else if(replacementPolicy.compare("1")==0){
        rep_candidate=LRU(cacheRepPolicyModify);
    }
    return rep_candidate;
}


int cacheClass::LRU(blockStruct& cacheLRUModify){
//int cacheClass::LRU(blockStruct cacheLRUModify){
    std:: cout << "(cacheClass::LRU)" << std::endl;
    int lru=0;
    int lruway=0;
    lru=cacheLRUModify[cpuAddrIndex][0].leastRecentUsedCounterBit;
    std::cout << "(cacheClass::lru, pre for loop) lru: " << lru << std::endl;
    for(int j=1;j<setAssociativity;j++){
        if(cacheLRUModify[cpuAddrIndex][j].leastRecentUsedCounterBit<lru){
            lru=cacheLRUModify[cpuAddrIndex][j].leastRecentUsedCounterBit;
            std::cout << "(cacheClass::lru, inside forloop, inside if) lru: " << lru << std::endl;
            lruway=j;
        }
    }
    return lruway;
}