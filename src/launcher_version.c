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
#include "../inc/movement.h"
#include "../inc/launcher_version.h"
#include "../inc/threading_part.h"
#include "../inc/multiple_threads.h"
#include "../inc/movement_sem.h"

#include <pthread.h>
// assuming the number of threads for t1 is 4
#define VERSION 3

void launch_version(struct execution *ptr_execut, grid *map);


void * (*launcher[VERSION][VERSION])(void *)  =
{{&automata_movement,&automata_movement,&multiple_movement },
 {&automata_movement,&automata_synchronized_sem,&multple_synchronized_sem },
{0, 0, 0}};





/**
*throw the version of the game assuming paramater are in the struct execution.
* param @ptr_execut tne data given by user
* param @map map of the game
**/
void launch_version(struct execution *ptr_execut, grid *map) {
    map->people = ptr_execut->nb_people;
    void * (*tmp)(void*) = launcher[ptr_execut->mode][ptr_execut->version];
    switch (ptr_execut->version) {
        case 0:
            // launch version 1
            create_single_thread(map, tmp);
            break;
        case 1:
            // launch version 2
            create_threads(map, tmp);
            break;
        case 2:
            multiple_threads(map, tmp);
            // launch version 3
            break;
    }
  }
