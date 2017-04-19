//
// Created by Nick Chapman on 4/19/17.
//

#ifndef PAGING_LFUSIMULATION_H
#define PAGING_LFUSIMULATION_H


#include <queue>
#include "PagingSimulation.h"

using Pair = std::pair<unsigned int, PageTableEntry*>;

class LfuSimulation : PagingSimulation {
    static struct _FrequencyComparator {
        bool operator()(std::pair<unsigned int, PageTableEntry*>* const& lhs,
                        std::pair<unsigned int, PageTableEntry*>* const& rhs) {
            return lhs->first > rhs->first;
        }
    } FrequencyComparator;

    std::vector<Pair*> mFrequencyQueue;
    std::unordered_map<unsigned int, Pair*> mIteratorMap;
public:
    LfuSimulation();

    LfuSimulation(unsigned int nFrames, bool verbose);

    void UpdateEntry(PageTableEntry* entry);

    PageTableEntry* RemoveFrameEntry();

    void AddFrameEntry(PageTableEntry* entry);

    void Process();
};


#endif //PAGING_LFUSIMULATION_H
