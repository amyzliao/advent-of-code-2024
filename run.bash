#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: run.bash [-p] <dayfolder>"
  exit 1
fi

# print output to file
if [ "$1" == "-p" ]; then
  dayfolder=$2
  cd $dayfolder
  ./main > out.out
  cd ..

# dont print output to file
else
  dayfolder=$1
  cd $dayfolder
  ./main
  cd ..
fi
