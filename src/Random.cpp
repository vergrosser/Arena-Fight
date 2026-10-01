#include "Random.h"

std::mt19937 Random::generator{std::random_device{}()};
std::uniform_int_distribution<int> Random::XRand{0, X_MAX - 1};
std::uniform_int_distribution<int> Random::YRand{0, Y_MAX - 1};
std::uniform_int_distribution<int> Random::ColorRand{0, 255};
std::uniform_real_distribution<double> Random::floatRand{0.0, 1.0};

float Random::ProbValue() {
    return static_cast<float>(floatRand(generator));
}

std::pair<int, int> Random::PosValue(){
    return std::pair<int, int>(static_cast<int>(XRand(generator)), static_cast<int>(YRand(generator)));
}

Color Random::ColorValue(){
    uint32_t value = generator();

    return {
        static_cast<uint8_t>(value & 0xFF),
        static_cast<uint8_t>((value >> 8) & 0xFF),
        static_cast<uint8_t>((value >> 16) & 0xFF)
    };
}