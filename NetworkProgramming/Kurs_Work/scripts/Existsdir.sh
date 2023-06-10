#!/bin/bash

L=$(pwd)
cd "$2"
if [ -d "$3" ]
then
cd "$3"
echo "$(pwd)" > $L/temp/$1.txt
fi
