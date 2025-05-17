#!/bin/bash
set -e

# Create build directory
mkdir -p build
cd build

# Install dependencies with Conan
conan install .. --build=missing

# Configure and build with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

echo "Build completed successfully!" 