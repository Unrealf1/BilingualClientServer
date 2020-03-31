#!/bin/bash

client="./build/client"
if [ -f "$client" ]; then
    ./${client}
else 
    echo "$client does not exist"
    echo "run client/build.sh first"
fi
