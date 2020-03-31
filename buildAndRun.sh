#!/bin/bash

cycles=1

if [ $# -gt 0 ]
then
    cycles=$1
fi

err=$(./buildAll.sh 2>&1 >/dev/tty)
if [ -z "${err}" ]
then
    echo "Build complete."
    ./runClientServer.sh $cycles
else
    echo "Build failed"
fi
