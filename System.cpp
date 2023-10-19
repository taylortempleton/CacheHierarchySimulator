#include <math.h>
#include <vector>  
#include <iostream>
#include <iomanip>

#include "System.h"


void System::buildCaches(
                int addressLength, 
                int cacheBlockSize, 
                int L1cacheSize, 
                int L1setAssociativity, 
                int L2cacheSize,
                int L2setAssociativity){

    addressLength_ = addressLength; 
    cacheBlockSize_ = cacheBlockSize; 
    L1cacheSize_ = L1cacheSize;
    L1setAssociativity_ = L1setAssociativity;
    L2cacheSize_ = L2cacheSize;
    L2setAssociativity_ = L2setAssociativity;

}

//void System::decode(unsigned long long cpuAddress, int L1indexWidth, int L1offsetWidth){
void System::decode(unsigned long long cpuAddress, int L1indexWidth, int L1offsetWidth, int L2indexWidth, int L2offsetWidth){
    // Decode for 12bit addresses
    L1decodedTag_ = (cpuAddress & 0xFC0)>>(L1indexWidth + L1offsetWidth);
    L1decodedIndex_=(cpuAddress & 0x20)>>(L1offsetWidth);
    L1decodedOffset_ = (cpuAddress & 0x1F);

    L2decodedTag_ = (cpuAddress & 0xFC0)>>(L2indexWidth + L2offsetWidth);
    L2decodedIndex_=(cpuAddress & 0x20)>>(L2offsetWidth);
    L2decodedOffset_ = (cpuAddress & 0x1F);

}

void System::printCfg(){
    std::cout << std::endl;
    std::cout << "************* Simulation Config *************" << std::endl;
    std::cout << "addressLength_: " << std::dec << addressLength_ << std::endl;
    std::cout << "cacheBlockSize_: " << cacheBlockSize_ << std::endl;
    std::cout << "L1cacheSize_: " << L1cacheSize_ << std::endl;
    std::cout << "L1setAssociativity_: " <<  L1setAssociativity_ << std::endl;
    std::cout << "L2cacheSize_ : " << L2cacheSize_ << std::endl;
    std::cout << "L2setAssociativity_: " << L2setAssociativity_ << std::endl;
    std::cout << std::endl;
}

void System::printTabulate(
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
                int L2writeTotal){


                float L1missRate =   (float)(L1readMisses + L1writeMisses)/(float)(L1readTotal + L1writeTotal);
                float L2missRate =   (float)(L2readMisses + L2writeMisses)/(float)(L2readTotal + L2writeTotal);

                int totalMemoryTraffic = L2readMisses + L2writeMisses + L2writeBacks;



            std::cout << "************* Simulation Results *************" << std::endl;
            std::cout << "Total # of Addresses: " << addressCounter << std::endl;


            std::cout << std::endl;
            std::cout << "L1 Cache" << std::endl;
            std::cout << "  L1readHits: " << L1readHits << std::endl;
            std::cout << "  L1readMisses: " << L1readMisses << std::endl;
            std::cout << "  L1writeHits: " << L1writeHits << std::endl;
            std::cout << "  L1writeMisses: " << L1writeMisses << std::endl;
            std::cout << "  L1readTotal: " << L1readTotal << std::endl;
            std::cout << "  L1writeTotal: " << L1writeTotal << std::endl;
            std::cout << "  L1writeBacks: " << L1writeBacks << std::endl;
            std::cout << "  L1missRate: " << std::setprecision(3) << L1missRate << std::endl;
            std::cout << std::endl;
            std::cout << "L2 Cache" << std::endl;
            std::cout << "  L2readHits: " << L2readHits << std::endl;
            std::cout << "  L2readMisses: " << L2readMisses << std::endl;
            std::cout << "  L2writeHits: " << L2writeHits << std::endl;
            std::cout << "  L2writeMisses: " << L2writeMisses << std::endl;
            std::cout << "  L2readTotal: " << L2readTotal << std::endl;
            std::cout << "  L2writeTotal: " << L2writeTotal << std::endl;
            std::cout << "  L2writeBacks: " << L2writeBacks << std::endl;
            std::cout << "  L2missRate: " << std::setprecision(3) << L2missRate << std::endl;
            std::cout << std::endl;
            std::cout << "  totalMemoryTraffic (L2<->mainmem): " << totalMemoryTraffic << std::endl;


}
