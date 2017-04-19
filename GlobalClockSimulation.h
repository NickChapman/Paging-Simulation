//
// Created by Nick Chapman on 4/18/17.
//

#ifndef PAGING_GLOBALCLOCKSIMULATION_H
#define PAGING_GLOBALCLOCKSIMULATION_H

#include "PagingSimulation.h"

class GlobalClockSimulation : public PagingSimulation {
public:
    GlobalClockSimulation();

    GlobalClockSimulation(unsigned int nFrames, bool verbose);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);

    void Process();
};


#endif //PAGING_GLOBALCLOCKSIMULATION_H
