#pragma once

#include "neuron.h"
#include <vector>
#include "pre.h"

class Connection{
    public:
    Neuron begin;
    Neuron end;
    float weight = 0.0f;
};