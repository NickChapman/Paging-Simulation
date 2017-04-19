//
// Created by Nick Chapman on 4/18/17.
//

#ifndef PAGING_PAGETABLE_H
#define PAGING_PAGETABLE_H

#include <map>
#include <iostream>
#include <unordered_map>
#include "PageTableEntry.h"

class PagingSimulation {
protected:
    static const unsigned int cMaxPageNumber = 1048576;
    static const unsigned int cPageSize = 4096;
    bool verbose;
    unsigned int mNFrames;
    std::unordered_map<unsigned int, PageTableEntry*> mFrames;

public:
    PagingSimulation();

    PagingSimulation(unsigned int nFrames, bool verbose = false);

    virtual void Process();

    virtual PageTableEntry* RemoveFrameEntry() = 0;

    virtual void AddFrameEntry(PageTableEntry* entry) = 0;
};

#endif //PAGING_PAGETABLE_H
