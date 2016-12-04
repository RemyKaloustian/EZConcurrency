/**
 * Multiple threads part is used for the t2 of the application.
 * we manage the movement of an unique person on the map
 * every thread manage only one person.*
 *
 * author : @CésarCollé
 * created :  08/09/2016
 *
 * */

#include "../inc/multiple_threads.h"
#include "../inc/movement.h"
#include "../inc/designer.h"
#include "../inc/monitor.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>

extern sem_t mutex_multiple;
extern sem_t terminaison;
extern struct monitor monitoring;

void * multiple_movement(void * data){
    struct multiple_movement *ptr_data = data;
    person * current = &ptr_data->map->population[ptr_data->rank];
    while (current->x >= X_FINAL) {
        delete_entity(ptr_data->map, current->x, current->y);
        move_person(ptr_data->map, current);
        draw_entity(ptr_data->map, current->x, current->y);
    }
    delete_entity(ptr_data->map, current->x, current->y);
    free(data);
    return NULL;
}

void * multple_synchronized_sem(void * data){
    struct multiple_movement *ptr_data = data;
    person * current = &ptr_data->map->population[ptr_data->rank];
    while (current->x >= X_FINAL) {
        sem_wait(&mutex_multiple);
        delete_entity(ptr_data->map, current->x, current->y);
        move_person(ptr_data->map, current);
        draw_entity(ptr_data->map, current->x, current->y);
        sem_post(&mutex_multiple);
    }
    sem_post(&terminaison);
    delete_entity(ptr_data->map, current->x, current->y);
    free(data);
    return NULL;
}


void * multple_synchronized_monitor(void * data){
    struct multiple_movement *ptr_data = data;
    person * current = &ptr_data->map->population[ptr_data->rank];
    while (current->x >= X_FINAL) {
        monitoring.get(&monitoring);
        delete_entity(ptr_data->map, current->x, current->y);
        move_person(ptr_data->map, current);
        draw_entity(ptr_data->map, current->x, current->y);
        monitoring.release(&monitoring);
    }
    sem_post(&terminaison);
    delete_entity(ptr_data->map, current->x, current->y);
    free(data);
    return NULL;
}
