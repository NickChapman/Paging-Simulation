//
// Created by Nick Chapman on 4/19/17.
//

#ifndef PAGING_OWNSIMULATION_H
#define PAGING_OWNSIMULATION_H


#include <random>
#include <list>
#include "PagingSimulation.h"

class OwnSimulation : public PagingSimulation {
    unsigned int mSinceLastHit = 0;
    unsigned int mRandomReplacementsRemaining = 0;
    std::mt19937 mt;
    std::uniform_int_distribution<unsigned int> dist;
    std::list<PageTableEntry*> cacheList;
    std::unordered_map<unsigned int, std::list<PageTableEntry*>::iterator> cacheMap;
public:
    OwnSimulation();

    OwnSimulation(unsigned int nFrames, bool verbose);

    void UpdateEntry(PageTableEntry* entry);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);

    void Process();

};


#endif //PAGING_OWNSIMULATION_H
