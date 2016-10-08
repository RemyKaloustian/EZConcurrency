#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################


for i in `seq 0 9`;
do
for j in `seq 0 2`;
do
    ./executable.exe -t $(i) -p $(j) -m
done
done