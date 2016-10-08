#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################


#for i in `seq 0 9`;
#do
#for j in `seq 0 2`;
#do
#    ./executable.exe -t "$j" -p "$i" -m
#done
#done

#./executable.exe -p 0 -t 0 -m
#./executable.exe -p 1 -t 0 -m
#./executable.exe -p 2 -t 0 -m
#./executable.exe -p 3 -t 0 -m
#./executable.exe -p 4 -t 0 -m
#./executable.exe -p 5 -t 0 -m
#./executable.exe -p 6 -t 0 -m
#./executable.exe -p 7 -t 0 -m
#./executable.exe -p 8 -t 0 -m
#./executable.exe -p 9 -t 0 -m



./executable.exe -p 0 -t 1 -m > version1.txt
./executable.exe -p 1 -t 1 -m >> version1.txt
./executable.exe -p 2 -t 1 -m >> version1.txt
./executable.exe -p 3 -t 1 -m >> version1.txt
./executable.exe -p 4 -t 1 -m >> version1.txt
./executable.exe -p 5 -t 1 -m >> version1.txt
./executable.exe -p 6 -t 1 -m >> version1.txt
./executable.exe -p 7 -t 1 -m >> version1.txt
./executable.exe -p 8 -t 1 -m >> version1.txt
./executable.exe -p 9 -t 1 -m >> version1.txt


