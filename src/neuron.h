#pragma once

#include "pre.h"

enum Type{
    input, output, hidden, none
};

class Neuron{
    public:
    float value = 0.0f;
    Type type = none;
    int id = -1;
};