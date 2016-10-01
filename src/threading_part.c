#include <stdio.h>
#include <pthread.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
//#include "../inc/determinism_travel.h"

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

pthread_t single_thread;



/*
*manage the partitionning of the map by the threads
* Assuming we bouhnd the part of thread on all the map .
**/
void manage_partition(struct execution * ptr_execution, int rank ){


}

void create_single_thread(grid* map){

  //Creating the single thread
  if(pthread_create(&single_thread, NULL, move_elem, NULL)){
    fprintf(stderr, "Error creating thread\n");
		return 1;
  }

//Joining the thread
  if(pthread_join(single_thread, NULL)){
    fprintf(stderr, "Error joining thread\n");
		return 1;
  }

}//create_single_thread()





void create_threads(struct execution * ptr_execution){
  pthread_t threads[THREADS_MAX];
  //
  // for (size_t i = 0; i < ptr_execution->nb_threads; i++) {
  //   pthread_create(&threads[i], NULL, run, ptr_execution);
  // }

}
