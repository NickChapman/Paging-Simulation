//
// Created by Nick Chapman on 4/19/17.
//

#include "RandomSimulation.h"

RandomSimulation::RandomSimulation() {
    this->mt = std::mt19937(this->rd());

}
