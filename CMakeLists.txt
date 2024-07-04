cmake_minimum_required(VERSION 3.10)

# Set the project name
project(newCatan)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(newCatan
        main.cpp
        Game.cpp
        Player.cpp
        Board.cpp
        Plot.cpp
        Resource.cpp
        development_card.cpp
)

# Include directories
target_include_directories(newCatan PUBLIC "${PROJECT_BINARY_DIR}")
