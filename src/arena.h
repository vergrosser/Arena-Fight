#pragma once

#include "entity.h"
#include "pre.h"
#include <array>
#include "Random.h"
#include <iostream>


class Arena{
    public:
    std::array<std::array<int, X_MAX>, Y_MAX> playground{};
    std::array<Entity, POPULATION> entities;
    Arena();
    Entity newRandom();
    void Simulate();
    Entity newBaby(Entity father, Entity mother);
    void Reproduce();
    void Render();
};

