#include "main.h"

int main(){
    Arena arena;
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < STEP_PER_GEN; j++){
            arena.Simulate();
        }
        std::cout << "Generation " << i + 1 << ": ";
        arena.Reproduce();
    }
    return 0;
}