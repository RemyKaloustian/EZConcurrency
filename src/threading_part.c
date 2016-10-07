#include <stdio.h>
#include <pthread.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"
//#include "../inc/determinism_travel.h"
#include "../inc/multiple_threads.h"

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
    affic_grid(map);
}				//create_single_thread()





void
create_threads (grid * map)
{
    printf("In create_threads()\n");
  pthread_t threads[THREADS_MAX];
    memset(threads, 0, THREADS_MAX);
    struct movement movements[THREADS_MAX] = {{map,  0, 256, 0, 64}, {map, 256, 512, 0, 64}, {map, 0, 256, 64, 128}, {map, 256, 512, 64, 128}};

   for (size_t i = 0; i < THREADS_MAX; i++) {
        printf("create %d threads \n", i);
       if(pthread_create(&threads[i], NULL, automata_movement, &movements[i])){
           fprintf(stderr, "Error creating thread\n");
           exit(1);
       }
   }
//    void * status;
    printf("fin creation thread  \n");
    for (size_t j = 0; j < THREADS_MAX; ++j) {
        printf("join %d  thread \n", j);
        if(pthread_join(threads[j], NULL))
        {
            fprintf (stderr, "Error joining thread \n");
            exit(5);
        }
    }
    printf("\n Final  : \n");
    affic_grid(map);
}



void multiple_threads(grid * map){
    printf("Multiple threads %d ! \n", map->people);
    int size_threads = map->people;
    pthread_t pthreads[size_threads];

    struct multiple_movement *move;
    memset(pthreads, 0, size_threads);
    for (int i = 0; i <size_threads; ++i) {
        printf("boucle creation thread i = : %d\n", i);
        move = calloc(1, sizeof(struct multiple_movement));
        move->map = map;
        move->rank = i;
        printf("je met : %p\n", &move);
        if ( pthread_create(&pthreads[i], NULL, multiple_movement, move)) {
            fprintf(stderr, "error creating multiple threads");
            exit(0);
        }
    }
    for (size_t j = 0; j < size_threads; ++j) {
        if(pthread_join(pthreads[j], NULL))
        {
            fprintf (stderr, "Error joining thread \n");
            exit(5);
        }
    }
    affic_grid(map);

}