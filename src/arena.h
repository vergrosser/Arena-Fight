#pragma once

#include "entity.h"
#include "pre.h"
#include <array>
#include "Random.h"
#include <iostream>
#include <SFML/Graphics.hpp>


class Arena{
    public:
    std::array<std::array<int, X_MAX>, Y_MAX> playground{};
    std::array<Entity, POPULATION> entities;
    Arena();
    Entity newRandom();
    void Simulate();
    Entity newBaby(Entity father, Entity mother);
    void Reproduce();
    void Render(sf::RenderWindow& window, const sf::Font& font, int generation, int step);
    float currrentProb = 0.0f;
};

