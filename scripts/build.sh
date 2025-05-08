#!/bin/sh
# cLLM build script
# It is a shell script that sets up the environment and builds the project using cmake.
# It is designed to be run from the command line.
# The script first checks if the build directory exists, and if not, creates it.
# It then changes to the build directory and runs cmake with the appropriate options.
# Finally, it runs the make command to build the project.
# The script also includes options for building with different configurations (debug, release, etc.)


# detect whether ../cllm__build exists
if [ ! -d ../cllm_build ]; then
    mkdir ../cllm_build
else
    echo "Build directory already exists. Clean ../cllm_build first."
    rm -r ../cllm_build/*
fi 


cmake -S . -B ../cllm_build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCLLLM_BUILD_TESTS=OFF \

cmake --build ../cllm_build --config Release --target install