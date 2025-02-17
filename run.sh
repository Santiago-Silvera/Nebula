#!/bin/bash

# Create build directory and run cmake
cmake -S . -B build

# Change to build directory
cd build

# Build the project using make
make

# Go back to the root directory
cd ..

# Run the render executable
./build/render
