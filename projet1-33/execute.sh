#!/usr/bin/env bash
#################################
#                               #
#   Execution of the project    #
#                               #
#################################
EXE="./bin/executable.exe"
echo $1
echo "salut les noob"
if [ "$1" = "bench" ]; then
  echo "stat bench"
  for k in `seq 0 1`;
  do
  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
      $EXE -t "$j" -p "$i" -m -e "$k"
  done
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
    $EXE -t "$j" -p "$i" -m -e 0 >> ./output/data.txt
  done
  done
  echo "version sans semaphore"
  python ./test/graph_analyse.py ./output/data.txt
  echo > ./output/data_sem.txt

  for i in `seq 0 9`;
  do
  for j in `seq 0 2`;
  do
    $EXE -t "$j" -p "$i" -m -e 1>> ./output/data_sem.txt
  done
  done
  python ./test/graph_analyse.py ./output/data_sem.txt &


else
  $EXE -t 1 -p 4 -m
fi
