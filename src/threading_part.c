/**
 *  Threading part
 *
 * author : @CésarCollé
 * 08/10/2016
 *
 * Assuming the program have to compute different version of the game
 * we build a threading_part where the program will create the threads asociate to
 * each version.
 *
 * We can notice the automata_movement is throwed in the t0 and t1 version.
 * Indeed we notice that we juste have to make boundaries for each process.
 * that's the reason why t0 have as boundary the whole map and in t1 we split the same map
 * in 4 part.
 *
 * */


#include <stdio.h>
#include <pthread.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"
#include "../inc/multiple_threads.h"
#include "../inc/designer.h"

#define MIDDLE {256, 64, PERSON}
/*
 * we define boundaries
 *
 * */
#define TOP_RIGHT_CORNER {{DEFAULT_GRID_WIDTH, 0}, MIDDLE}}
#define TOP_LEFT_CORNER {{0, DEFAULT_GRID_WIDTH}, MIDDLE}
#define BOTTOM_LEFT_CORNER {{DEFAULT_GRID_HEGHT, 0}}
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

void
create_single_thread(grid *map) {

    struct movement single_movement = {map, 0, 512, 0, 128};

    //Creating the single thread
    if (pthread_create(&single_thread, NULL, automata_movement, &single_movement)) {
        fprintf(stderr, "Error creating thread\n");
        exit(1);
    }

//Joining the thread
    if (pthread_join(single_thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        exit(1);
    }
}                //create_single_thread()



/**
 *
 * Linked to the t1 version .
 * we create 4 threads and we attribute at each one boundary
 * and the automata movement process to the movements of each person.
 *
 * */

void
create_threads(grid *map) {
    pthread_t threads[THREADS_MAX];
    memset(threads, 0, THREADS_MAX);
    // define all boundarie of these 4 threads. these boundaries will split
    // the map in some piece and restraint the actions of each thread to the proper person.
    struct movement movements[THREADS_MAX] = {{map, 0,   256, 0,  64},
                                              {map, 256, 512, 0,  64},
                                              {map, 0,   256, 64, 128},
                                              {map, 256, 512, 64, 128}};

    // create THREADS_MAX = 4 threads
    for (size_t i = 0; i < THREADS_MAX; i++) {
        // throw the automata_movement
        if (pthread_create(&threads[i], NULL, automata_movement, &movements[i])) {
            fprintf(stderr, "Error creating thread\n");
            exit(1);
        }
    }
    for (size_t j = 0; j < THREADS_MAX; ++j) {
        if (pthread_join(threads[j], NULL)) {
            fprintf(stderr, "Error joining thread \n");
            exit(5);
        }
    }
}


void multiple_threads(grid *map) {
    int size_threads = map->people;
    pthread_t pthreads[size_threads];

    struct multiple_movement *move;
    memset(pthreads, 0, size_threads);
    for (int i = 0; i < size_threads; ++i) {
        move = calloc(1, sizeof(struct multiple_movement));
        move->map = map;
        move->rank = i;
        if (pthread_create(&pthreads[i], NULL, multiple_movement, move)) {
            fprintf(stderr, "error creating multiple threads");
            exit(0);
        }
    }
    for (size_t j = 0; j < size_threads; ++j) {
        if (pthread_join(pthreads[j], NULL)) {
            fprintf(stderr, "Error joining thread \n");
            exit(5);
        }
    }

}