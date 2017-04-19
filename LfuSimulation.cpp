//
// Created by Nick Chapman on 4/19/17.
//

#include "LfuSimulation.h"

LfuSimulation::LfuSimulation() : PagingSimulation() {
    this->mFrequencyQueue = std::vector<Pair*>();
    std::make_heap(this->mFrequencyQueue.begin(), this->mFrequencyQueue.end(), LfuSimulation::FrequencyComparator);
    this->mIteratorMap = std::unordered_map<unsigned int, Pair*>();
}

LfuSimulation::LfuSimulation(unsigned int nFrames, bool verbose) : PagingSimulation(nFrames, verbose) {
    this->mFrequencyQueue = std::vector<Pair*>();
    std::make_heap(this->mFrequencyQueue.begin(), this->mFrequencyQueue.end(), LfuSimulation::FrequencyComparator);
    this->mIteratorMap = std::unordered_map<unsigned int, Pair*>();
}

void LfuSimulation::UpdateEntry(PageTableEntry* entry) {
    Pair* pair = this->mIteratorMap.at(entry->mVpn);
    pair->first += 1;
    std::make_heap(this->mFrequencyQueue.begin(), this->mFrequencyQueue.end(), LfuSimulation::FrequencyComparator);
}

PageTableEntry* LfuSimulation::RemoveFrameEntry() {
    std::pop_heap(this->mFrequencyQueue.begin(), this->mFrequencyQueue.end(), LfuSimulation::FrequencyComparator);
    Pair *back = this->mFrequencyQueue.back();
    PageTableEntry* removed = back->second;
    this->mFrequencyQueue.pop_back();
    this->mIteratorMap.erase(removed->mVpn);
    this->mFrames.erase(removed->mVpn);
    delete back;
    return removed;
}

void LfuSimulation::AddFrameEntry(PageTableEntry* entry) {
    this->mFrames.emplace(entry->mVpn, entry);
    this->mFrequencyQueue.push_back(new Pair(1, entry));
    Pair* pair = this->mFrequencyQueue.back();
    this->mIteratorMap.emplace(entry->mVpn, pair);
    std::push_heap(this->mFrequencyQueue.begin(), this->mFrequencyQueue.end(), LfuSimulation::FrequencyComparator);
}

void LfuSimulation::Process() {
    unsigned int accesses = 0;
    unsigned int misses = 0;
    unsigned int writes = 0;
    unsigned int drops = 0;
    // Read in all of the memory accesses and process them accordingly
    unsigned int address;
    char action;
    while (std::cin >> std::hex >> address >> action) {
        PageTableEntry* entry;
        accesses += 1;
        // Calculate the VPN
        unsigned int vpn = address / this->cPageSize;
        // Check if the page is in the frames
        if (this->mFrames.count(vpn) == 1) {
            entry = this->mFrames.at(vpn);
            this->UpdateEntry(entry);
            // It's in the frames and it's a hit!
            // If it's a write then this dirties the page
            if (action == 'W') {
                entry->mDirty = true;
            }
            else {
                // Since it's just reading we can continue
                continue;
            }
        }
        else {
            // It's a miss
            misses += 1;
            entry = new PageTableEntry(vpn);
            // Check if our frames are full yet
            PageTableEntry* removed = nullptr;
            if (this->mFrames.size() >= this->mNFrames) {
                // It's full so remove one
                removed = this->RemoveFrameEntry();
                // Put the removed one back into the general page table
                // Put the new one into the frames
                this->AddFrameEntry(entry);
                // Check if we had to write
                if (removed->mDirty) {
                    removed->mDirty = false;
                    if (this->verbose) {
                        std::cout << "Page 0x" << std::hex << removed->mVpn << " swaps page 0x" << vpn << std::endl;
                    }
                    writes += 1;
                }
                else {
                    if (this->verbose) {
                        std::cout << "Page 0x" << std::hex << removed->mVpn << " overwrites page 0x" << vpn
                                  << std::endl;
                    }
                    drops += 1;
                }
            }
            else {
                // The frames aren't full yet
                this->AddFrameEntry(entry);
            }
            // Finally check whether we have dirtied the page we just brought in
            if (action == 'W') {
                entry->mDirty = true;
            }
        }
    }
    // Print out the results of processing the file
    std::cout << "Number of memory accesses: " << accesses << std::endl;
    std::cout << "Number of misses: " << misses << std::endl;
    std::cout << "Number of writes: " << writes << std::endl;
    std::cout << "Number of drops: " << drops << std::endl;
}




