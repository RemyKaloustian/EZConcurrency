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
#include <unistd.h>


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
