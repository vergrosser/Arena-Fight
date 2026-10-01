#include "arena.h"
#include <algorithm>



Arena::Arena(){
    for(int i = 0; i < POPULATION; i++){
        entities[i] = newRandom();
        playground[entities[i].y_pos][entities[i].x_pos] = 1; 
    }
}

std::vector<Connection> RandomConnection(Brain& brain){
    std::vector<Connection> connections;
    auto tryConnect = [&](Neuron& begin, Neuron& end){
        if (CONNECTION_PROBABILITY == 0.0f){
            return;
        }

        if (CONNECTION_PROBABILITY < 1.0f &&
            Random::ProbValue() >= CONNECTION_PROBABILITY){
            return;
        }

        Connection connection;
        connection.begin = begin;
        connection.end = end;
        connection.weight = Random::ProbValue() * 2.0f - 1.0f;
        connections.push_back(connection);
    };

    for (auto& input : brain.input_neurons){
        for (auto& hidden : brain.hidden_neurons){
            tryConnect(input, hidden);
        }
    }

    for (auto& hidden : brain.hidden_neurons){
        for (auto& output : brain.output_neurons){
            tryConnect(hidden, output);
        }
    }

    for (auto& input : brain.input_neurons){
        for (auto& output : brain.output_neurons){
            tryConnect(input, output);
        }
    }

    return connections;
}

Entity Arena::newRandom(){
    Entity entity;
    auto position = Random::PosValue();
    while(playground[position.second][position.first] != 0){
        position = Random::PosValue();
    }
    entity.x_pos = position.first;
    entity.y_pos = position.second;
    entity.color = Random::ColorValue();
    Brain brain;
    for(int i = 4; i < INPUT_NEURONS_COUNT; i++){
        brain.input_neurons[i].value = Random::ProbValue();
    }
    brain.connections = RandomConnection(brain);
    entity.brain = brain;
    entity.brain.input_neurons[0].value = static_cast<float>(X_MAX - entity.x_pos) / (X_MAX + 1);
    entity.brain.input_neurons[1].value = static_cast<float>(entity.x_pos) / (X_MAX + 1);
    entity.brain.input_neurons[2].value = static_cast<float>(Y_MAX - entity.y_pos) / (Y_MAX + 1);
    entity.brain.input_neurons[3].value = static_cast<float>(entity.y_pos) / (Y_MAX + 1);
    return entity;
}

void Mutation(Connection& connection){
    if(Random::ProbValue() >= MUTATION_PROBABILITY)
        return;
    
    connection.weight += (Random::ProbValue() * 2.0f - 1.0f) * 0.1f;
    connection.weight = std::max(-1.0f, std::min(1.0f, connection.weight));
}

Entity Arena::newBaby(Entity father, Entity mother){
    Entity baby;
    auto position = Random::PosValue();
    while(playground[position.second][position.first] != 0){
        position = Random::PosValue();
    }
    baby.x_pos = position.first;
    baby.y_pos = position.second;
    Brain brain;
    std::pair<int, int> mofa_count{};
    for(int i = 4; i < INPUT_NEURONS_COUNT; i++){
        brain.input_neurons[i].value = static_cast<float>((father.brain.input_neurons[i].value + mother.brain.input_neurons[i].value)/2.0);
    }
    auto sameConnection = [](const Connection& a, const Connection& b){
        return a.begin.type == b.begin.type && a.begin.id == b.begin.id &&
               a.end.type == b.end.type && a.end.id == b.end.id;
    };
    auto inherit = [&](Connection connection, bool fromFather){
        const auto existing = std::find_if(brain.connections.begin(), brain.connections.end(),
            [&](const Connection& candidate){ return sameConnection(candidate, connection); });
        if(existing != brain.connections.end())
            return;
        Mutation(connection);
        brain.connections.push_back(connection);
        if(fromFather)
            mofa_count.second++;
        else
            mofa_count.first++;
    };
    for(const auto& connection: father.brain.connections){
        const auto match = std::find_if(mother.brain.connections.begin(), mother.brain.connections.end(),
            [&](const Connection& candidate){ return sameConnection(candidate, connection); });
        if(match != mother.brain.connections.end()){
            const bool fromFather = Random::ProbValue() < 0.5f;
            inherit(fromFather ? connection : *match, fromFather);
        } else if(Random::ProbValue() < 0.5f){
            inherit(connection, true);
        }
    }
    for(const auto& connection: mother.brain.connections){
        const auto match = std::find_if(father.brain.connections.begin(), father.brain.connections.end(),
            [&](const Connection& candidate){ return sameConnection(candidate, connection); });
        if(match == father.brain.connections.end() && Random::ProbValue() < 0.5f){
            inherit(connection, false);
        }
    }
    baby.brain = brain;
    baby.brain.input_neurons[0].value = static_cast<float>(X_MAX - baby.x_pos) / (X_MAX + 1);
    baby.brain.input_neurons[1].value = static_cast<float>(baby.x_pos) / (X_MAX + 1);
    baby.brain.input_neurons[2].value = static_cast<float>(Y_MAX - baby.y_pos) / (Y_MAX + 1);
    baby.brain.input_neurons[3].value = static_cast<float>(baby.y_pos) / (Y_MAX + 1);
    const int inheritedCount = mofa_count.first + mofa_count.second;
    const float fatherWeight = inheritedCount > 0 ?
        static_cast<float>(mofa_count.second) / inheritedCount : 0.5f;
    const float motherWeight = 1.0f - fatherWeight;
    baby.color = {
        static_cast<int>(father.color.R * fatherWeight + mother.color.R * motherWeight),
        static_cast<int>(father.color.G * fatherWeight + mother.color.G * motherWeight),
        static_cast<int>(father.color.B * fatherWeight + mother.color.B * motherWeight)
    };
    return baby;
}

void Arena::Reproduce(){
    std::vector<Entity> survived_entities;
    for(auto& entity: entities){
        if(entity.x_pos > 60 && entity.x_pos <96 )
            survived_entities.push_back(entity);
    }

    static std::mt19937 generator{std::random_device{}()};
    playground = {};
    for(auto& entity: entities){
        if(survived_entities.empty()){
            entity = newRandom();
        } else {
            std::uniform_int_distribution<std::size_t> fatherRand(0, survived_entities.size() - 1);
            const std::size_t fatherIndex = fatherRand(generator);
            std::size_t motherIndex = fatherIndex;
            if(survived_entities.size() > 1){
                std::uniform_int_distribution<std::size_t> motherRand(0, survived_entities.size() - 2);
                motherIndex = motherRand(generator);
                if(motherIndex >= fatherIndex)
                    motherIndex++;
            }
            entity = newBaby(survived_entities[fatherIndex], survived_entities[motherIndex]);
        }
        if(entity.x_pos >= 0 && entity.x_pos < X_MAX &&
           entity.y_pos >= 0 && entity.y_pos < Y_MAX){
            playground[entity.y_pos][entity.x_pos] = 1;
        }
    }
    std::cout << survived_entities.size() << " / " << POPULATION << '\n';
}

void Arena::Simulate(){
    for(auto & entity: this-> entities){
        for(auto& neuron: entity.brain.output_neurons){
            neuron.value = 0.0f;
        }
        auto newHiddenNeurons = entity.brain.hidden_neurons;
        for(auto& neuron: newHiddenNeurons){
            neuron.value = 0.0f;
        }
        for (const auto& connection : entity.brain.connections)
        {
            float src = connection.begin.type == hidden ? entity.brain.hidden_neurons[connection.begin.id].value : entity.brain.input_neurons[connection.begin.id].value;
            float& dest = (connection.end.type == hidden ? newHiddenNeurons[connection.end.id].value : entity.brain.output_neurons[connection.end.id].value);
            dest += src * connection.weight;
        }
        entity.brain.hidden_neurons = newHiddenNeurons;

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};
        int bestDirection = -1;
        float bestValue = 0.0f;

        if(entity.x_pos < 0 || entity.x_pos >= X_MAX ||
           entity.y_pos < 0 || entity.y_pos >= Y_MAX){
            continue;
        }

        for(int direction = 0; direction < 4; direction++){
            const int nextX = entity.x_pos + dx[direction];
            const int nextY = entity.y_pos + dy[direction];

            if(nextX < 0 || nextX >= X_MAX || nextY < 0 || nextY >= Y_MAX){
                continue;
            }
            if(playground[nextY][nextX] != 0){
                continue;
            }

            const float value = entity.brain.output_neurons[direction].value;
            if(bestDirection == -1 || value > bestValue){
                bestDirection = direction;
                bestValue = value;
            }
        }

        if(bestDirection != -1){
            playground[entity.y_pos][entity.x_pos] = 0;
            entity.x_pos += dx[bestDirection];
            entity.y_pos += dy[bestDirection];
            entity.brain.input_neurons[0].value = static_cast<float>(X_MAX - entity.x_pos) / (X_MAX + 1);
            entity.brain.input_neurons[1].value = static_cast<float>(entity.x_pos) / (X_MAX + 1);
            entity.brain.input_neurons[2].value = static_cast<float>(Y_MAX - entity.y_pos) / (Y_MAX + 1);
            entity.brain.input_neurons[3].value = static_cast<float>(entity.y_pos) / (Y_MAX + 1);
            playground[entity.y_pos][entity.x_pos] = 1;
        }
    }
}

void Arena::Render(){

}