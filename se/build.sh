#!/bin/bash

export PATH=/home/Shawn/bin:/usr/local/bin:/usr/bin:/bin:/opt/bin:/c/Maxim/Toolchain/bin
cd ..


if [ "$1" = "debug" ]; then
    opt="DEBUG=1"
else
    opt="DEBUG=0"
fi
if [ "$2" = "clean" ]; then
  make clean
fi

make ${opt} VERBOSE=1
