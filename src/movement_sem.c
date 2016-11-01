#include "../inc/movement_sem.h"
#include "../inc/movement.h"
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/designer.h"

#include<signal.h>

static sem_t mutex;

grid *Map;

void sighandler_sem(int signo) {
    printf("CTRL-C %p \n", Map);
    affic_grid(Map);
    for (int i = 0; i < Map->people; ++i) {
        if (Map->population[i].x > 15)
            printf("  x: %d y:%d  ", Map->population[i].x, Map->population[i].y);
    }
    printf(" \n");
    exit(7);
}


void *automata_synchronized_sem(void *param_ptr_data) {
    struct movement *ptr_data = param_ptr_data;
    printf("%d\n", SIGINT);
    signal(SIGINT, sighandler_sem);
    Map = ptr_data->ptr_grid;
    int cpt = 0;

#ifdef DEBUG
    Map = ptr_data->ptr_grid;
#endif
    sem_init(&mutex, 0, 1);
    while (is_done(ptr_data->ptr_grid->population, ptr_data->ptr_grid->people)) {
        for (int i = 0; i < ptr_data->ptr_grid->people; ++i) {

            if (is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)
                && ptr_data->ptr_grid->population[i].x >= 15) {

#ifdef DEBUG
                printf("processus : %d %d %d %d manage x:%d y:%d: \n",
                       ptr_data->left_bound, ptr_data->top_bound,
                       ptr_data->right_bound, ptr_data->bottom_bound,
                        ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
#endif
                sem_wait(&mutex);
                move_person(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i]);
                if (!check_done(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i])) {

                    draw_entity(ptr_data->ptr_grid, ptr_data->ptr_grid->population[i].x,
                                ptr_data->ptr_grid->population[i].y);

                } else {
                    ptr_data->ptr_grid->population[i].current_status = DONE;
                }
                sem_post(&mutex);
            }

        }
    }
    return NULL;
}


void critical_section(grid *map, person *p) {

}
