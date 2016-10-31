#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################
EXE="./bin/executable.exe"
echo $1

if [ "$1" = "bench" ]; then
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
      $EXE -t "$j" -p "$i" -m

  done
  done
elif [ "$1" = "bench_plot" ]; then
  rm -r -f output
  mkdir output
  echo > ./output/data.txt
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
    $EXE -t "$j" -p "$i" -m >> ./output/data.txt
  done
  done
  python ./test/graph_analyse.py ./output/data.txt

else
  $EXE -t 1 -p 4 -m
fi
