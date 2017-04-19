#include <iostream>
#include <string>
#include "FifoSimulation.h"
#include "GlobalClockSimulation.h"
#include "LruSimulation.h"
#include "RandomSimulation.h"
#include "LfuSimulation.h"
#include "OwnSimulation.h"

void PrintUsage() {
    std::string usage = "nlc35.exe <number of frames> <algorithm to use> [verbose]";
    std::string algorithms = "\tFIFO: First In, First Out\n\tGC: Global Clock\n\tLFU: Least Frequently Used\n\tLRU: Least Recently Used\n\tRAND: Random\n\tOWN: LRU Antithrashing";
    std::cout << "Usage: " << usage << std::endl;
    std::cout << "Available algorithms:" << std::endl;
    std::cout << algorithms << std::endl;
}

int main(int argc, char* argv[]) {
    // We turn off synchronization with stdin and stdout
    // This means we can't use printf and scanf but they're
    // bad practice in c++ anyway
    std::ios_base::sync_with_stdio(false);
    bool verbose = false;
    if (argc != 3 && argc != 4) {
        PrintUsage();
        exit(1);
    }
    if (argc == 4 && std::string(argv[3]) == "verbose") {
        verbose = true;
    }
    unsigned int nFrames = std::stoul(argv[1]);
    std::string algo = std::string(argv[2]);
    PagingSimulation* simulation;
    if (algo == "FIFO") {
        simulation = new FifoSimulation(nFrames, verbose);
    }
    else if (algo == "GC") {
        simulation = new GlobalClockSimulation(nFrames, verbose);
    }
    else if (algo == "LRU") {
        simulation = new LruSimulation(nFrames, verbose);
    }
    else if (algo == "LFU") {
        simulation = new LfuSimulation(nFrames, verbose);
    }
    else if (algo == "RAND") {
        simulation = new RandomSimulation(nFrames, verbose);
    }
    else if (algo == "OWN") {
        simulation = new OwnSimulation(nFrames, verbose);
    }
    else {
        PrintUsage();
        exit(1);
    }
    simulation->Process();
}
