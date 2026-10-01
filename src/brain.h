#pragma once

#include "neuron.h"
#include "connection.h"
#include <vector>
#include <array>
#include "pre.h"


class Brain{
    
    public:
    Brain();
    std::array<Neuron, INPUT_NEURONS_COUNT> input_neurons;
    std::array<Neuron, OUTPUT_NEURONS_COUNT> output_neurons;
    std::array<Neuron, HIDDEN_NEURONS_COUNT> hidden_neurons;
    std::vector<Connection> connections;
};