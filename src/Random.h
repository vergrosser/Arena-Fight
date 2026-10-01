#pragma once

#include <random>
#include <utility>
#include "pre.h"

class Random{
    static std::mt19937 generator;
    static std::uniform_int_distribution<int> XRand;
    static std::uniform_int_distribution<int> YRand;
    static std::uniform_real_distribution<double> floatRand;
    static std::uniform_int_distribution<int> ColorRand;
    public:
    static std::pair<int, int> PosValue();
    static float ProbValue();
    static Color ColorValue();
};