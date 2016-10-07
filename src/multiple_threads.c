//
// Created by caesar on 10/7/16.
//

#include "../inc/multiple_threads.h"
#include "../inc/movement.h"
#include "../inc/elements.h"
#include <unistd.h>


void * multiple_movement(void * data){
    printf("je reçois  : %p\n", data);
    struct multiple_movement *ptr_data = data;
    printf("multiple movement !! rank : %d  \n", ptr_data->rank);
    //affic_grid(ptr_data->map);
    person * current = &ptr_data->map->population[ptr_data->rank];

    while (current->x >= X_FINAL) {
        sleep(1);
        printf("proc %d manipule x = %d y = %d  ", ptr_data->rank, current->x, current->y);
        delete_entity(ptr_data->map, current->x, current->y);
        move_person(ptr_data->map, current);
        printf("TO x = %d y = %d \n", current->x, current->y);

        draw_entity(ptr_data->map, current->x, current->y);
    }
    delete_entity(ptr_data->map, current->x, current->y);
    free(data);
    return NULL;
}
