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
#include "../inc/UITools.h"

#include<signal.h>

grid *Map;

extern sem_t mutex;

extern sem_t terminaison;


void sighandler_sem(int signo) {
    fflush(stdout);
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
    //printf("%d\n", SIGINT);
    //Map = ptr_data->ptr_grid;
#ifndef DEBUG
  signal(SIGINT, sighandler_sem);
    Map = ptr_data->ptr_grid;
    char pass = 0;
#endif

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
              if ( ptr_data->ptr_grid->population[i].y <= 68){
                sem_wait(&mutex);
                pass = 1;
              }
                move_person(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i]);
                //MOVING THE PERSON WITH SDL
                //sleep(1);
#ifdef GRAPH
                usleep(50000);
                UI_reset();
                UI_draw_walls();
                UI_draw_person(&pixel_person,ptr_data->ptr_grid->population[i].x,ptr_data->ptr_grid->population[i].y);
                UI_update();

                if(SDL_PollEvent(&event)){
                  switch(event.type){
                    case SDL_QUIT:
                      return 0;
                  }
                }
#endif


#ifdef DEBUG
                printf("\nafter move \n");
                printf("move :x = %d y = %d \n", ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
                printf("realease\n");
#endif
                if (!check_done(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i])) {

                    draw_entity(ptr_data->ptr_grid, ptr_data->ptr_grid->population[i].x,
                                ptr_data->ptr_grid->population[i].y);

                } else {
                    ptr_data->ptr_grid->population[i].current_status = DONE;
                }
            }
            if (pass){
              sem_post(&mutex);
              pass = 0;
            }

        }
    }
    sem_post(&terminaison);
    return NULL;
}




void automata_synchroning(){

}


void critical_section(grid *map, person *p) {

}
