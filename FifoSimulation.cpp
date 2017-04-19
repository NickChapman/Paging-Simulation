//
// Created by Nick Chapman on 4/18/17.
//

#include "FifoSimulation.h"

FifoSimulation::FifoSimulation() : PagingSimulation() {
    this->queue = std::list<PageTableEntry*>();
}

FifoSimulation::FifoSimulation(unsigned int nFrames, bool verbose) : PagingSimulation(nFrames, verbose) {
    this->queue = std::list<PageTableEntry*>();
}

PageTableEntry* FifoSimulation::RemoveFrameEntry() {
    PageTableEntry* removed = this->queue.front();
    this->queue.pop_front();
    this->mFrames.erase(removed->mVpn);
    return removed;
}

void FifoSimulation::AddFrameEntry(PageTableEntry* entry) {
    this->queue.push_back(entry);
    this->mFrames.emplace(entry->mVpn, entry);
    return;
}
