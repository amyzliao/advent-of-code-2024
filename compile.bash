#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: compile.bash <dayfolder>"
  exit 1
fi

dayfolder=$1
cd $dayfolder

if [ "$dayfolder" == "day6" ]; then
  clang++ main.cpp part1.cpp -o main
else
  clang++ main.cpp -o main
fi

cd ..