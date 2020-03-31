#!/bin/bash

cd client
./build.sh
cd ../server
./build.sh
cd ../test
./test.sh
cd ..

