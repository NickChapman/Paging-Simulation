//
// Created by Nick Chapman on 4/19/17.
//

#include "OwnSimulation.h"

OwnSimulation::OwnSimulation() {
    this->mt = std::mt19937(std::random_device{}());
    this->dist = std::uniform_int_distribution<unsigned int>(0, UINT32_MAX);
}

OwnSimulation::OwnSimulation(unsigned int nFrames, bool verbose) : PagingSimulation(nFrames, verbose) {
    this->mt = std::mt19937(std::random_device{}());
    this->dist = std::uniform_int_distribution<unsigned int>(0, UINT32_MAX);
}

void OwnSimulation::UpdateEntry(PageTableEntry* entry) {
    this->mSinceLastHit = 0;
    auto it = this->cacheMap.at(entry->mVpn);
    this->cacheList.splice(this->cacheList.begin(), this->cacheList, it);
}

PageTableEntry* OwnSimulation::RemoveFrameEntry() {
    this->mSinceLastHit += 1;
    PageTableEntry* removed;
    if (this->mSinceLastHit > this->mFrames.size() || this->mRandomReplacementsRemaining) {
        // We are at risk of trashing so we will replace at random
        // Check if we are just starting this
        if (this->mRandomReplacementsRemaining == 0) {
            // We are just starting our thrashing prevention so allocate a block of random replacements
            this->mRandomReplacementsRemaining = this->mNFrames;
        }
        else {
            // We are in the middle of thrashing prevention so use one of our random replacements
            this->mRandomReplacementsRemaining -= 1;
        }
        unsigned long advance = this->dist(this->mt) % this->mFrames.size();
        auto it = this->mFrames.begin();
        std::advance(it, advance);
        removed = it->second;
        // Need to remove it from the cache
        auto cachePosition = this->cacheMap.at(removed->mVpn);
        this->cacheList.erase(cachePosition);
        this->cacheMap.erase(removed->mVpn);
    }
    else {
        removed = this->cacheList.back();
        this->cacheList.pop_back();
        this->cacheMap.erase(removed->mVpn);
        this->mFrames.erase(removed->mVpn);
    }
    return removed;
}

void OwnSimulation::AddFrameEntry(PageTableEntry* entry) {
    this->cacheList.push_front(entry);
    this->cacheMap.emplace(entry->mVpn, this->cacheList.begin());
    this->mFrames.emplace(entry->mVpn, entry);
}

void OwnSimulation::Process() {
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
                        std::cout << "Page 0x" << std::hex << vpn << " swaps page 0x" << removed->mVpn << std::endl;
                    }
                    writes += 1;
                }
                else {
                    if (this->verbose) {
                        std::cout << "Page 0x" << std::hex << vpn << " overwrites page 0x" << removed->mVpn
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
