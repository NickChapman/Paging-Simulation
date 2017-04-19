//
// Created by Nick Chapman on 4/18/17.
//

#ifndef PAGING_PAGETABLEENTRY_H
#define PAGING_PAGETABLEENTRY_H


class PageTableEntry {
public:
    unsigned int mVpn;
    bool mDirty;
    bool mClock;

    PageTableEntry(unsigned int vpn) {
        this->mVpn = vpn;
        this->mDirty = false;
    }
};


#endif //PAGING_PAGETABLEENTRY_H
