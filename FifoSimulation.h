//
// Created by Nick Chapman on 4/18/17.
//

#ifndef PAGING_FIFOSIMULATION_H
#define PAGING_FIFOSIMULATION_H

#include <list>
#include "PagingSimulation.h"

class FifoSimulation : public PagingSimulation {
    std::list<PageTableEntry*> queue;
public:
    FifoSimulation();

    FifoSimulation(unsigned int nFrames, bool verbose = false);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);
};


#endif //PAGING_FIFOSIMULATION_H
