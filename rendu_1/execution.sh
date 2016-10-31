#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################
EXE="./bin/executable.exe"

if [ "$0" = "bench" ]; then
  echo  > ./test/data.txt
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
      $(EXE) -t "$j" -p "$i" -m

  done
  done
elif [ "$0" = "bench_plot" ]; then
  echo  > ./test/data.txt
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do

    mkdir ./output
    echo > ./output/data.txt
    $(EXE) -t "$j" -p "$i" -m >> ./output/data.txt
    python ./test/graph_analyse.py ./output/data.txt
  done
  done
else
  echo $EXE -t 1 -p 4 -m
  $EXE -t 1 -p 4 -m
fi




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
#
#
#
#./executable.exe -p 0 -t 1 -m > version1.txt
#./executable.exe -p 1 -t 1 -m >> version1.txt
#./executable.exe -p 2 -t 1 -m >> version1.txt
#./executable.exe -p 3 -t 1 -m >> version1.txt
#./executable.exe -p 4 -t 1 -m >> version1.txt
#./executable.exe -p 5 -t 1 -m >> version1.txt
#./executable.exe -p 6 -t 1 -m >> version1.txt
#./executable.exe -p 7 -t 1 -m >> version1.txt
#./executable.exe -p 8 -t 1 -m >> version1.txt
#./executable.exe -p 9 -t 1 -m >> version1.txt
