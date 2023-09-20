#include "cacheClass.h"
#include <iostream>


void cacheClass::readCache(cacheStruct readCacheModify[][32]){
    int counter=0;
    int counter2=0;
    int rep_candidate=0;
    totalReads+=1;
    policyCounter+=1;
    // replacementPolicy = 0 for LRU
    if(replacementPolicy.compare("0")==0){
        for(int j=0;j<setAssociativity;j++){
            // Read hit
            if(readCacheModify[cpuAddrIndex][j].validBit==1 && (readCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
            readHits+=1;
            counter=1;
            readCacheModify[cpuAddrIndex][j].policycounter=policyCounter;
            break;
            }
        }
        // Read miss
        if(counter==0){
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
            readCacheModify[cpuAddrIndex][rep_candidate].policycounter=policyCounter;
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
                counter=1;
                break;
            }
        }
    // Read miss
    if(counter==0){
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
        readCacheModify[cpuAddrIndex][rep_candidate].policycounter=policyCounter;
        readCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=0;
        readCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
    }
    }
}


void cacheClass::writeCache(cacheStruct writeCacheModify[][32]){
    int counter=0,counter2=0,rep_candidate=0;
    totalWrites+=1;
    policyCounter+=1;
    //replacementPolicy = 0 for LRU
    if(replacementPolicy.compare("0")==0){
        for(int j=0;j<setAssociativity;j++){
        // Write hit
        if(writeCacheModify[cpuAddrIndex][j].validBit==1 && (writeCacheModify[cpuAddrIndex][j].cacheTagField==cpuAddrTagField)){
            writeHits+=1;
            counter=1;
            writeCacheModify[cpuAddrIndex][j].policycounter=policyCounter;
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
                writeCacheModify[cpuAddrIndex][rep_candidate].policycounter=policyCounter;
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
        writeCacheModify[cpuAddrIndex][rep_candidate].policycounter=policyCounter;
        writeCacheModify[cpuAddrIndex][rep_candidate].dirtyBit=1;
        writeCacheModify[cpuAddrIndex][rep_candidate].validBit=1;
    }
    }
}


int cacheClass::cacheRepPolicy(cacheStruct cacheRepPolicyModify[][32]){
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


int cacheClass::LRU(cacheStruct cacheLRUModify[][32]){
    int lru=0,lruway=0;
    lru=cacheLRUModify[cpuAddrIndex][0].policycounter;
    for(int j=1;j<setAssociativity;j++){
        if(cacheLRUModify[cpuAddrIndex][j].policycounter<lru){
            lru=cacheLRUModify[cpuAddrIndex][j].policycounter;
            lruway=j;
        }
    }
    return lruway;
}