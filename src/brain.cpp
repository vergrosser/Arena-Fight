#include "brain.h"

Brain::Brain(){
    for(int i = 0; i < INPUT_NEURONS_COUNT; i++){
        input_neurons[i].type = input;
        input_neurons[i].id = i;
    }
    for(int i = 0; i < OUTPUT_NEURONS_COUNT; i++){
        output_neurons[i].type = output;
        output_neurons[i].id = i;
    }
    for(int i = 0; i < HIDDEN_NEURONS_COUNT; i++){
        hidden_neurons[i].type = hidden;
        hidden_neurons[i].id = i;
    }
}