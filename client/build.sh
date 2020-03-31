#!/bin/bash

echo "Building the client..."

if [ ! -d "./build" ]; then
	mkdir ./build
fi

cd build

cmake ../ $@

make

cd ..