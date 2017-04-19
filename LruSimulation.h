//
// Created by Nick Chapman on 4/19/17.
//

#ifndef PAGING_LRUSIMULATION_H
#define PAGING_LRUSIMULATION_H

#include <list>
#include "PagingSimulation.h"

class LruSimulation : public PagingSimulation {
    std::list<PageTableEntry*> cacheList;
    std::unordered_map<unsigned int, std::list<PageTableEntry*>::iterator> cacheMap;
public:
    LruSimulation();

    LruSimulation(unsigned int nFrames, bool verbose);

    void UpdateEntry(unsigned int vpn);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);

    void Process();

};


#endif //PAGING_LRUSIMULATION_H
