#!/bin/bash

L=$(pwd)
cd $2
if [ -f "$3" ]
then
echo "$(pwd)/$(basename "$3")" > $L/temp/$1.txt
fi
