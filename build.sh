#!/bin/bash

# creating directory build if not exist
mkdir -p build
cd build

# running cmake
cmake ..

# running make
make

# copy program data
cp -r ../data build/bin/

# returning to root directory
cd ../../../
