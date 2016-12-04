#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################
EXE="bin/executable.exe"
echo $1
if [ "$1" = "bench" ]; then
  echo "version 1"
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
    $EXE -t "$j" -p "$i" -m -e 2
  done
  done
elif [ "$1" = "bench_plot" ]; then
  echo "let's make a bench plot"
  rm -r -f output
  mkdir output
  echo > ./output/data.txt
  echo "HeHé"
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
    $EXE -t "$j" -p "$i" -m -e 1 >> ./output/data.txt
  done
  done
  python ./test/graph_analyse.py ./output/data.txt

else
  PATH_="$(cd "$(dirname "$0")"&&pwd)"/
  echo "version 2"
  $PATH_$EXE -t 1 -p 2 -m -e 2
  #$EXE -t 1 -p 2 -m -e 1
fi
