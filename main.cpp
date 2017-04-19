#include <iostream>
#include "FifoSimulation.h"
#include "GlobalClockSimulation.h"
#include "LruSimulation.h"

int main() {
    // We turn off synchronization with stdin and stdout
    // This means we can't use printf and scanf but they're
    // bad practice in c++ anyway
    std::ios_base::sync_with_stdio(false);
    LruSimulation simulation = LruSimulation(2, true);
    simulation.Process();
}