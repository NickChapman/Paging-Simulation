//
// Created by Nick Chapman on 4/19/17.
//

#include "LruSimulation.h"

LruSimulation::LruSimulation() : PagingSimulation() {
    this->cacheList = std::list<PageTableEntry*>();
    this->cacheMap = std::unordered_map<unsigned int, std::list<PageTableEntry*>::iterator>();
}

LruSimulation::LruSimulation(unsigned int nFrames, bool verbose) : PagingSimulation(nFrames, verbose) {
    this->cacheList = std::list<PageTableEntry*>();
    this->cacheMap = std::unordered_map<unsigned int, std::list<PageTableEntry*>::iterator>();
}

void LruSimulation::UpdateEntry(unsigned int vpn) {
    auto it = this->cacheMap.at(vpn);
    this->cacheList.splice(this->cacheList.begin(), this->cacheList, it);
}

PageTableEntry* LruSimulation::RemoveFrameEntry() {
    // Take the entry off of the back
    PageTableEntry* entry = this->cacheList.back();
    this->cacheList.pop_back();
    this->cacheMap.erase(entry->mVpn);
    this->mFrames.erase(entry->mVpn);
    return entry;
}

void LruSimulation::AddFrameEntry(PageTableEntry* entry) {
    this->cacheList.push_front(entry);
    this->cacheMap.emplace(entry->mVpn, this->cacheList.begin());
    this->mFrames.emplace(entry->mVpn, entry);
}

void LruSimulation::Process() {
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
            this->UpdateEntry(entry->mVpn);
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
            // It wasn't in the frames, so check to see if we have a record
            // for it in our disk yet
            if (this->mDisk.count(vpn) == 1) {
                entry = this->mDisk.at(vpn);
                this->mDisk.erase(vpn);
            }
            else {
                // This is the first time we have seen this page and we need to make it
                entry = new PageTableEntry(vpn);
            }
            // Check if our frames are full yet
            PageTableEntry* removed = nullptr;
            if (this->mFrames.size() >= this->mNFrames) {
                // It's full so remove one
                removed = this->RemoveFrameEntry();
                // Put the removed one back into the general page table
                this->mDisk.emplace(removed->mVpn, removed);
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

