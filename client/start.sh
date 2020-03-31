#!/bin/bash

client="./build/client"
if [ -f "$client" ]; then
    ./${client} $1
else 
    echo "$client does not exist"
    echo "run client/build.sh first"
fi
