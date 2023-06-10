#!/bin/bash

L=$(pwd)
cd $2
res=$(ls -1l)
echo "$res" > $L/temp/$1.txt
