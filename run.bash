#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: run.bash <dayfolder>"
  exit 1
fi

dayfolder=$1
cd $dayfolder
./main
cd ..