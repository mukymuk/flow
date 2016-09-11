#!/bin/bash

export PATH=/home/Shawn/bin:/usr/local/bin:/usr/bin:/bin:/opt/bin:/c/Maxim/Toolchain/bin
cd ..

if [ "$1" = "clean" ]; then
  make clean
fi

make
