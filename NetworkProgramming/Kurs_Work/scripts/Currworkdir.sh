#!/bin/bash

L=$(pwd)
cd $2
cd $3
res=$(pwd)
echo $res > $L/temp/$1.txt
