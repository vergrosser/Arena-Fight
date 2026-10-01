#pragma once

#define INPUT_NEURONS_COUNT 4
#define OUTPUT_NEURONS_COUNT 4
#define HIDDEN_NEURONS_COUNT 3
#define CONNECTION_COUNT 6

#define STEP_PER_GEN 100

#define POPULATION 1000

#define X_MAX 128
#define Y_MAX 128

#define MUTATION_PROBABILITY 0.1

#define CONNECTION_PROBABILITY 0.7

struct Color{
    int R, G, B;
    Color operator+(const Color& another){
        Color hlp;
        hlp.R = R + another.R;
        hlp.G = G + another.G;
        hlp.B = B + another.B;
        return hlp;
    }
    Color operator*(int multp){
        Color hlp;
        hlp.R = R * multp;
        hlp.G = G * multp;
        hlp.B = B * multp;
        return hlp;
    }
};