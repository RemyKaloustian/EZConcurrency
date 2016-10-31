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
#include "../inc/threading_part.h"

/*
*manage the partitionning of the map by the threads
* Assuming we bouhnd the part of thread on all the map .
**/
pthread_t single_thread;

void
create_single_thread(grid *map, void*(*funct)(void*)) {

    struct movement single_movement = {map, 0, 512, 0, 128};

    //Creating the single thread
    if (pthread_create(&single_thread, NULL, funct, &single_movement)) {
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
create_threads(grid *map, void*(*funct)(void*)) {
    pthread_t threads[THREADS_MAX];
    memset(threads, 0, THREADS_MAX);
    // define all boundarie of these 4 threads. these boundaries will split
    // the map in some piece and restraint the actions of each thread to the proper person.
    struct movement movements[THREADS_MAX] = {{map, 0,   256, 0,  64},
                                              {map, 257, 512, 0,  64},
                                              {map, 0,   256, 65, 128},
                                              {map, 256, 512, 65, 128}};

    // create THREADS_MAX = 4 threads
    for (size_t i = 0; i < THREADS_MAX; i++) {
        // throw the automata_movement
        if (pthread_create(&threads[i], NULL, *funct, &movements[i])) {
            fprintf(stderr, "Error creating thread\n");
            exit(6);
        }
    }
    for (size_t j = 0; j < THREADS_MAX; ++j) {
        if (pthread_join(threads[j], NULL)) {
            fprintf(stderr, "Error joining thread \n");
            exit(5);
        }
    }
}


void multiple_threads(grid *map, void*(*funct)(void*)) {
    int size_threads = map->people;
    pthread_t pthreads[size_threads];
    struct multiple_movement *move;
    memset(pthreads, 0, size_threads);
    for (int i = 0; i < size_threads; ++i) {
        move = calloc(1, sizeof(struct multiple_movement));
        move->map = map;
        move->rank = i;
        if (pthread_create(&pthreads[i], NULL, *funct, move)) {
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
