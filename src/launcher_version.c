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
#include <pthread.h>
// assuming the number of threads for t1 is 4
#define NUMBER_THREADS 4

// temporary
void * run(void * ptr){
  return NULL;
}
/**
*throw the version of the game assuming paramater are in the struct execution.
* param @ptr_execut tne data given by user
* param @map map of the game
**/
void launch_version(struct execution * ptr_execut, grid * map){
  pthread_t threads[4];
  switch(ptr_execut->version){
    case 0:
      // launch version 1
      break;
   case 1:
      // launch version 2
      create_threads(ptr_execution);
      break;
  case 2:
    // launch version 3
    break;


  }




}
