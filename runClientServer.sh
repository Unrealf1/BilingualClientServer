#!/bin/bash

cd server
source start.sh
sleep 0.2

cd ../client

cycles=1
if [ $# -gt 0 ]
then
    cycles=$1
fi

for i in $(seq 1 $cycles)
do
    if [ $cycles -eq $i ]
    then
        ./start.sh
    else
        ./start.sh&
    fi
done
sleep 0.01

kill ${pid}

cd ..

