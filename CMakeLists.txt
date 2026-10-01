cmake_minimum_required(VERSION 3.16)

project(Nature LANGUAGES CXX)

add_executable(Nature
    src/main.cpp
    src/arena.cpp
    src/brain.cpp
    src/connection.cpp
    src/entity.cpp
    src/neuron.cpp
    src/Random.cpp
)

target_compile_features(Nature PRIVATE cxx_std_11)
target_include_directories(Nature PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")