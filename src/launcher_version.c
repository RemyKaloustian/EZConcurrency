/**
*
*launcher functions to load the good version of the game
* according to the -t option given by user.
*
*
* author : @CésarCollé
* 19 / 09 / 2016
***/

#include <stdio.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/threading_part.h"

#include <pthread.h>
// assuming the number of threads for t1 is 4
#define NUMBER_THREADS 4

// temporary
void *
run (void *ptr)
{
  return NULL;
}

/**
*throw the version of the game assuming paramater are in the struct execution.
* param @ptr_execut tne data given by user
* param @map map of the game
**/
void
launch_version (struct execution *ptr_execut, grid * map)
{
  map->people = ptr_execut->nb_people;
  pthread_t threads[4];
    printf("we launch version : %d\n", ptr_execut->version);
  switch (ptr_execut->version)
    {
    case 0:
      // launch version 1
      create_single_thread (map);
      break;
    case 1:
      // launch version 2
      create_threads (map);
      break;
    case 2:
        multiple_threads(map);
      // launch version 3
      break;


    }




}
