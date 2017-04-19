//
// Created by Nick Chapman on 4/19/17.
//

#ifndef PAGING_RANDOMSIMULATION_H
#define PAGING_RANDOMSIMULATION_H

#include <random>
#include "PagingSimulation.h"

class RandomSimulation : public PagingSimulation {
    std::mt19937 mt;
    std::uniform_int_distribution<unsigned int> dist;
public:
    RandomSimulation();

    RandomSimulation(unsigned int nFrames, bool verbose);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);
};


#endif //PAGING_RANDOMSIMULATION_H
