cmake_minimum_required(VERSION 3.16)

project(Nature LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Nature
    src/main.cpp
    src/arena.cpp
    src/brain.cpp
    src/connection.cpp
    src/entity.cpp
    src/neuron.cpp
    src/Random.cpp
)
target_compile_features(Nature PRIVATE cxx_std_17)
target_link_libraries(Nature PRIVATE SFML::Graphics)

target_compile_features(Nature PRIVATE cxx_std_11)
target_include_directories(Nature PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")