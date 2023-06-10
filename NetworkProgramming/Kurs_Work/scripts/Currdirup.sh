#!/bin/bash

L=$(pwd)
cd $2
cd ..
res=$(pwd)
echo $res > $L/temp/$1.txt
