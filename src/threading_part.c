#include <stdio.h>
#include <pthread.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/determinism_travel.h"

#define MIDDLE {256, 64, PERSON}
#define TOP_RIGHT_CORNER {{DEFAULT_GRID_WIDTH, 0}, MIDDLE}}
#define TOP_LEFT_CORNER {{0, DEFAULT_GRID_WIDTH}, MIDDLE}
#define BOTTOM_LEFT_CORNER {{DEFAULT_GRID_HEIGHT, 0}}
#define BOTTOM_RIGHT_CORNER {{0, DEFAULT_GRID_HEIGHT}}
#define THREADS_MAX 4



struct bound {
  cell top_right;
  cell top_down;
};



/*
*manage the partitionning of the map by the threads
* Assuming we bouhnd the part of thread on all the map .
**/
void manage_partition(struct execution * ptr_execution, int rank ){
    struct cell middle  = MIDDLE;

}


void * run (void * ptr){



}





void create_threads(struct execution * ptr_execution){
  pthread_t threads[THREADS_MAX];

  for (size_t i = 0; i < threads_number; i++) {
    pthread_create(&threads[i], NULL, run, ptr_execution);
  }

}
