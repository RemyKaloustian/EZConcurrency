#include <stdio.h>
#include <pthread.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"
//#include "../inc/determinism_travel.h"

#define MIDDLE {256, 64, PERSON}
#define TOP_RIGHT_CORNER {{DEFAULT_GRID_WIDTH, 0}, MIDDLE}}
#define TOP_LEFT_CORNER {{0, DEFAULT_GRID_WIDTH}, MIDDLE}
#define BOTTOM_LEFT_CORNER {{DEFAULT_GRID_HEGHT, 0}}
#define BOTTOM_RIGHT_CORNER {{0, DEFAULT_GRID_HEIGHT}}
#define THREADS_MAX 4



struct bound
{
  cell top_right;
  cell top_down;
};

pthread_t single_thread;



/*
*manage the partitionning of the map by the threads
* Assuming we bouhnd the part of thread on all the map .
**/
void
manage_partition (struct execution *ptr_execution, int rank)
{


}

void
create_single_thread (grid * map)
{

struct movement single_movement = {map,  0, 512, 0 , 128};

  //Creating the single thread
    printf("creation thread\n");
  if(pthread_create(&single_thread, NULL, automata_movement, &single_movement)){
    fprintf(stderr, "Error creating thread\n");
		exit(1);
  }

//Joining the thread
  if (pthread_join (single_thread, NULL))
    {
      fprintf (stderr, "Error joining thread\n");
      exit(1);
    }

}				//create_single_thread()





void
create_threads (grid * map)
{
    printf("In create_threads()\n");
  pthread_t threads[THREADS_MAX];
    memset(threads, 0, THREADS_MAX);
    struct movement movements[THREADS_MAX] = {{map,  0, 256, 0, 64}, {map, 256, 512, 0, 64}, {map, 0, 256, 64, 128}, {map, 256, 512, 64, 128}};

   for (size_t i = 0; i < THREADS_MAX; i++) {

       if(pthread_create(&threads[i], NULL, automata_movement, &movements[i])){
           fprintf(stderr, "Error creating thread\n");
           exit(1);
       }
   }
    void * status;
    printf("fin creation thread  \n");
    for (size_t j = 0; j < THREADS_MAX; ++j) {
        if(pthread_join(threads[j], status))
        {
            fprintf (stderr, "Error joining thread\n");
            exit(5);
        }
    }
    printf("\n Final  : \n");
    affic_grid(map);


}
