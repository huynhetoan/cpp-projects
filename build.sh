#!/bin/bash

echo "Building 3D Physics Engine..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
make -j$(nproc)

# Run the executable
echo ""
echo "Running physics engine demo..."
./bin/PhysicsEngine3D

echo "Build and run complete!"
