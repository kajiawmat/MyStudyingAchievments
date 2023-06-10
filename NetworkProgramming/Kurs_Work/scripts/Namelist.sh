#!/bin/bash

L=$(pwd)
cd $2
res=$(ls -1)
echo "$res" > $L/temp/$1.txt
