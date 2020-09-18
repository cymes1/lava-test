#!/bin/bash

# creating directory build if not exist
mkdir -p build
cd build || exit

# running cmake
cmake ..

# running make
make

# copy program data
cp -r ../data build/bin/

# running program
cd build/bin || exit
./vulkan-test

# returning to root directory
cd ../../../
