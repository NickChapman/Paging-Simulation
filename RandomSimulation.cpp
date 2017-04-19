//
// Created by Nick Chapman on 4/19/17.
//

#include "RandomSimulation.h"

RandomSimulation::RandomSimulation() {
    this->mt = std::mt19937(std::random_device{}());
    this->dist = std::uniform_int_distribution<unsigned int>(0, UINT32_MAX);
}

RandomSimulation::RandomSimulation(unsigned int nFrames, bool verbose) : PagingSimulation(nFrames, verbose) {
    this->mt = std::mt19937(std::random_device{}());
    this->dist = std::uniform_int_distribution<unsigned int>(0, UINT32_MAX);
}

PageTableEntry* RandomSimulation::RemoveFrameEntry() {
    unsigned long advance = this->dist(this->mt) % this->mFrames.size();
    auto it = this->mFrames.begin();
    std::advance(it, advance);
    PageTableEntry* removed = it->second;
    this->mFrames.erase(removed->mVpn);
    return removed;
}

void RandomSimulation::AddFrameEntry(PageTableEntry* entry) {
    this->mFrames.emplace(entry->mVpn, entry);
}
