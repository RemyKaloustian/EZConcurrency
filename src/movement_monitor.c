#include "../inc/monitor.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/designer.h"
#include "../inc/movement.h"
#include <semaphore.h>
#include <unistd.h>
#include<signal.h>

extern sem_t terminaison;
extern struct monitor monitoring;
grid *Map;


void sighandler_monitor(int signo) {
    fflush(stdout);
    affic_grid(Map);
    for (int i = 0; i < Map->people; ++i) {
        if (Map->population[i].x > 15)
            printf("  x: %d y:%d  ", Map->population[i].x, Map->population[i].y);
    }
    printf(" \n");
    exit(7);
}


void *automata_synchronized_monitor(void *param_ptr_data) {
    struct movement *ptr_data = param_ptr_data;
#ifndef DEBUG
  signal(SIGINT, sighandler_monitor);
    Map = ptr_data->ptr_grid;
#endif
  int cpt = 0;
    while (is_done(ptr_data->ptr_grid->population, ptr_data->ptr_grid->people)) {
        for (int i = 0; i < ptr_data->ptr_grid->people; ++i) {
            if (is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)
                && ptr_data->ptr_grid->population[i].x > 15) {

#ifdef DEBUG
                printf("processus : %d %d %d %d manage x:%d y:%d: \n",
                       ptr_data->left_bound, ptr_data->top_bound,
                       ptr_data->right_bound, ptr_data->bottom_bound,
                        ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
#endif
// section critique
                //sem_wait(&mutex);
                if (ptr_data->ptr_grid->population[i].y <= 60 || ptr_data->ptr_grid->population[i].y >= 68 ){
                  monitoring.get(&monitoring);
                  cpt = 1;
                }
                move_person(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i]);
#ifdef DEBUG
                printf("\nafter move \n");
                printf("move :x = %d y = %d \n", ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
                printf("realease\n");
#endif
                if (cpt){
                  monitoring.release(&monitoring);
                  cpt = 0;
                }

                if (!check_done(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i])) {

                    draw_entity(ptr_data->ptr_grid, ptr_data->ptr_grid->population[i].x,
                                ptr_data->ptr_grid->population[i].y);

                } else {
                    ptr_data->ptr_grid->population[i].current_status = DONE;
                }
            }
        }
    }
    sem_post(&terminaison);
    return NULL;
}
