#include <iostream>
#include <vector>

#include "Cache.h"
#include "System.h"

int main(int argc, char *argv[]){
    setbuf(stdout,NULL);

    // System-wide constants
    int addressLength = atoi(argv[1]); 
    int cacheBlockSize = atoi(argv[2]);
    int L1cacheSize = atoi(argv[3]);
    int L1setAssociativity = atoi(argv[4]);
    int L2cacheSize = atoi(argv[5]);
    int L2setAssociativity = atoi(argv[6]);

    // Set up system (encapsulates and builds caches)
    System s;    
    s.buildCaches(addressLength,cacheBlockSize, L1cacheSize, L1setAssociativity, L2cacheSize, L2setAssociativity);

    Cache L1;
    Cache L2;
    L1.setParameters(s.addressLength_, s.cacheBlockSize_, s.L1cacheSize_, s.L1setAssociativity_);
    L2.setParameters(s.addressLength_, s.cacheBlockSize_, s.L2cacheSize_, s.L2setAssociativity_);

    // Parse Memory Trace File
    int addressCounter = 0;
    char readOrWrite;
    unsigned long long cpuAddress;
    FILE *fp=fopen(argv[7],"r");
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
            fscanf(fp,"%c %llx\n",&readOrWrite,&cpuAddress);
            s.decode(cpuAddress, L1.indexWidth_, L1.offsetWidth_, L2.indexWidth_, L2.offsetWidth_);
                
            addressCounter++;
            std::cout << std::endl;
            std::cout << "*** Address #: "<< addressCounter << " ***" << std::endl;
            std::cout << "cpuAddress: " <<  std::hex << cpuAddress << std::endl;
            std::cout << "decodedTag_: " << s.L1decodedTag_ << std::endl;
            std::cout << "decodedIndex_: " << s.L1decodedIndex_ << std::endl;
            std::cout << "decodedOffset_: " << s.L1decodedOffset_ << std::endl;

            if(readOrWrite == 'w'){
                if(L1.write(s.L1decodedTag_, s.L1decodedIndex_, s.L1decodedOffset_, s.L1setAssociativity_, addressCounter)){
                    //done
                    std::cout<< "(main) L1 write hit -> done " << std::endl;
                } else {
                    std::cout << "(main) L1 write miss -> write L2" << std::endl;
                    L2.write(s.L2decodedTag_, s.L2decodedIndex_, s.L2decodedOffset_, s.L2setAssociativity_, addressCounter);
                } 
            }
            else if(readOrWrite == 'r'){
            
                if(L1.read(s.L1decodedTag_, s.L1decodedIndex_, s.L1decodedOffset_, s.L1setAssociativity_, addressCounter, L1.numCacheSets_)){
                    std::cout<< "(main) L1 read hit -> done " << std::endl;
                } else {
                    std::cout<< "(main) L1 read miss -> read L2 " << std::endl;
                    if(L2.read(s.L2decodedTag_, s.L2decodedIndex_, s.L2decodedOffset_, s.L2setAssociativity_, addressCounter, L2.numCacheSets_)){
                        // L2read True
                        std::cout<< "(main) L2 read true " << std::endl;
                    } else {
                        // L2read False
                        std::cout<< "(main) L1 read false " << std::endl;
                    }
                }
            }
        }; 
        fclose(fp);

            s.printCfg();
            std::cout << "L1 Cache" << std::endl;
            L1.printCfg();
            std::cout << "L2 Cache" << std::endl;
            L2.printCfg();
            s.printTabulate(addressCounter, L1.readHits,L1.readMisses, L1.readTotal, L1.writeBacks, L1.writeHits, L1.writeMisses, L1.writeTotal, L2.readHits, L2.readMisses, L2.readTotal, L2.writeBacks, L2.writeHits, L2.writeMisses, L2.writeTotal);

        return 0;
       }