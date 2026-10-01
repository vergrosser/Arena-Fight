#include "main.h"
#include <cstdlib>
#include <filesystem>

int main(){
    Arena arena;
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Fight Arena");
    window.setFramerateLimit(60);
    sf::Font font;
    const char* windowsDirectory = std::getenv("WINDIR");
    const auto fontPath = std::filesystem::path(windowsDirectory ? windowsDirectory : "C:/Windows") /
                          "Fonts/segoeui.ttf";
    if(!font.openFromFile(fontPath)){
        std::cerr << "Cannot open font: " << fontPath << '\n';
        return 1;
    }
    int generation = 1;
    int step = 0;
    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if(!window.isOpen())
            break;
        window.setView(sf::View(sf::FloatRect({0.0f, 0.0f}, {800.0f, 800.0f})));
        if(step == STEP_PER_GEN){
            arena.Reproduce();
            generation++;
            step = 0;
        }
        arena.Simulate();
        step++;
        arena.Render(window, font, generation, step);

    }
    return 0;
}