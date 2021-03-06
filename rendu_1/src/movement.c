#include "../inc/elements.h"
#include "../inc/designer.h"
#include "../inc/movement.h"

#include<signal.h>





#define MIN_FINAL_Y 60
#define MAX_FINAL_Y 67
#define NB_DIRECTION 3

grid * Map;
void sighandler(int signo)
{
    affic_grid(Map);
    for (int i = 0; i < Map->people; ++i) {
        if (Map->population[i].x > 15)
        printf("  x: %d y:%d    ", Map->population[i].x, Map->population[i].y);
    }
    printf(" \n");
    exit(7);
}

struct movement final = {0, 15, 59, 67};

// TODO #define MAX_FINAL_X 16

enum Direction {
    STOP,
    N,
    S,
    O,
    SO,
    NO
};


void make_choice(enum Direction *choice, person *current) {
    int y = current->y;
    if (y < MIN_FINAL_Y) {
        choice[0] = SO;
        choice[1] = O;
        choice[2] = S;
    } else if (y > MAX_FINAL_Y) {
        choice[0] = NO;
        choice[1] = O;
        choice[2] = N;
    } else {
        //printf("take defautl x:%d y:%d\n", current->x, current->y);
        choice[0] = O;
        if ((y - DEFAULT_GRID_HEIGHT / 2) < 0) {
            choice[1] = SO;
            choice[2] = S;
        } else if ((y - DEFAULT_GRID_HEIGHT / 2) > 0) {
            choice[1] = NO;
            choice[2] = N;
        } else {
            choice[1] = STOP;
            choice[2] = STOP;
        }
    }
}

int is_done(person *persons, int nb) {
    for (int i = 0; i < nb; ++i) {
        if (persons[i].x >= 15) {
           //printf("x:%d y:%d still alive %d \n", persons[i].x, persons[i].y, persons[i].it_alive);

            return 1;
        }

    }
    return 0;
}

int check_done(grid *grid, person *p) {
    if (p->x <= X_FINAL) {
        p->current_status = DONE;
        delete_entity(grid, p->x, p->y);
        //affic_grid(grid);
        return 1;
    }
    return 0;
}


void *automata_movement(void *param_ptr_data) {
    struct movement *ptr_data = param_ptr_data;
    signal(SIGINT, sighandler);
#ifdef DEBUG
    signal(SIGINT, sighandler);
    Map = ptr_data->ptr_grid;
#endif

    //going through the list of person
//    printf("processus: %d %d %d %d enter\n", ptr_data->left_bound, ptr_data->top_bound, ptr_data->right_bound, ptr_data->bottom_bound);
    while (is_done(ptr_data->ptr_grid->population, ptr_data->ptr_grid->people)) {
        for (int i = 0; i < ptr_data->ptr_grid->people; ++i) {
            //printf("in for\n");
            // if the person is into the bound of the processus and he's not finished Them :
            if (is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)
                && ptr_data->ptr_grid->population[i].x >= 15) {
#ifdef DEBUG
                printf("processus : %d %d %d %d manage x:%d y:%d: \n",
                       ptr_data->left_bound, ptr_data->top_bound,
                       ptr_data->right_bound, ptr_data->bottom_bound,
                        ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
#endif


                //Move the person
                //We need the ptr_date cuz we need to check the bounds and the spaces around the current person
                //We also need the person coordinates, so we pass the person
#ifdef DEBUG
                printf("i = %d x = %d y = %d to \n", i, ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);

#endif
                move_person(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i]);
#ifdef DEBUG
                printf("after move \n");
                printf("x = %d y = %d \n", ptr_data->ptr_grid->population[i].x, ptr_data->ptr_grid->population[i].y);
#endif
                       //ptr_data->ptr_grid->population[i].y);
                if (!check_done(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i])) {

                    draw_entity(ptr_data->ptr_grid, ptr_data->ptr_grid->population[i].x,
                                ptr_data->ptr_grid->population[i].y);

                } else {
                    ptr_data->ptr_grid->population[i].current_status = DONE;
#ifdef DEBUG
                    printf("Not In Nound for %d %d %d %d\n", ptr_data->bottom_bound, ptr_data->left_bound, ptr_data->right_bound, ptr_data->top_bound);
#endif
                }

            }
            else if (ptr_data->ptr_grid->population[i].x <= 15){
                ptr_data->ptr_grid->population[i].current_status = DONE;
            }
//            if (cpt++ == 200){
//                fprintf(stderr, "fin\n");
//                affic_grid(ptr_data->ptr_grid);
//                //exit(1);
//                break;
//            }
        }
    }
    return NULL;
    }//automata_movement()

    int is_in_bounds(person *current_person, struct movement *current_movement) {

        return current_person->x >= current_movement->left_bound &&
               current_person->x <= current_movement->right_bound &&
               current_person->y >= current_movement->top_bound && current_person->y <= current_movement->bottom_bound;
        //The person is on the right chunk of the map
    }//is_in_bounds()

// preCondition : every person we move are not eligible to finish the game

    int check_down(grid *map, int x, int y) {
        if (y + DEFAULT_PEOPLE_SIZE >= DEFAULT_GRID_HEIGHT) {
            return 0;
        }
        int line = y + DEFAULT_PEOPLE_SIZE;

        for (int j = x; j < x - DEFAULT_PEOPLE_SIZE; j--) {
            if (map->matrix[line][j].content == WALL) {
                return 0;
            }
        }
        return 1;
    }

    int check_up(grid *map, int x, int y) {
        if (y - 1 <= 0) {
            return 0;
        }
        y = y - 1;

        for (int j = x; j < x - DEFAULT_PEOPLE_SIZE; j--) {
            if (map->matrix[y][j].content == WALL) {
                return 0;

            }
        }

        return 1;
    }

    int check_left(grid *map, int x, int y) {
        x = x - DEFAULT_PEOPLE_SIZE;
        for (int j = y; j < y + DEFAULT_PEOPLE_SIZE; j++) {
            if (map->matrix[j][x].content == WALL) {
                return 0;
            }
        }
        return 1;
    }

    int check_up_left(grid *map, int x, int y) {
        int _y = y - 1;
        int _x = x - DEFAULT_PEOPLE_SIZE;
        if (y < 1)return 0;
        return (check_up(map, x, y) && check_left(map, x, y) && map->matrix[_y][_x].content != WALL);
    }

    int check_down_left(grid *map, int x, int y) {
        int _y = y + DEFAULT_PEOPLE_SIZE;
        int _x = x - DEFAULT_PEOPLE_SIZE;
        if (y < 1)return 0;
        return (check_up(map, x, y) && check_left(map, x, y) && map->matrix[_y][_x].content != WALL);
    }


    void move_person(grid * ptr_grid, person *current_person) {
        int i = 0;
        enum Direction direction[NB_DIRECTION + 1];
        memset(direction, 0, NB_DIRECTION + 1);
        make_choice(direction, current_person);
        delete_entity(ptr_grid, current_person->x, current_person->y);
        while (direction[i] != 0) {
#ifdef DEBUG
            //printf("je prend la direction : %d\n", direction[i]);
#endif
            switch (direction[i++]) {
                case STOP:
                    return;
                case O:
                    if (check_left(ptr_grid, current_person->x, current_person->y)) {
#ifdef DEBUG
                        printf("Ouest\n");

#endif
                        current_person->x--;
                        return;
                    }
                    break;

                case NO:
                    if (check_up_left(ptr_grid, current_person->x, current_person->y)) {
#ifdef DEBUG
                        printf("NO\n");

#endif
//                        delete_entity(ptr_grid, current_person->x, current_person->y);
                        current_person->x--;
                        current_person->y--;

                        return;
                    }
                    break;
                case SO:
#ifdef DEBUG
                    printf("SO\n");

#endif
                    if (check_down_left(ptr_grid, current_person->x, current_person->y)) {
                        //delete_entity(ptr_grid, current_person->x, current_person->y);
                        current_person->x--;
                        current_person->y++;

                        return;
                    }
                    break;
                case N:
                    if (check_up(ptr_grid, current_person->x, current_person->y)) {
#ifdef DEBUG
                        printf("N\n");

#endif
                        //delete_entity(ptr_grid, current_person->x, current_person->y);
                        current_person->y--;

                        return;
                    }
                    break;
                case S:
                    if (check_down(ptr_grid, current_person->x, current_person->y)) {
#ifdef DEBUG
                        printf("S\n");

#endif
                        //delete_entity(ptr_grid, current_person->x, current_person->y);
                        current_person->y++;

                        return;

                    }
                    break;
            }

        }
//        fprintf(stderr, "x:%d y:%d can't move\n", current_person->x, current_person->y);
//        draw_entity(ptr_grid, current_person->x, current_person->y);
//        if (block++ == 15000){
//            affic_grid(ptr_grid);
//            exit(5);
//        }


//First we check if the place we wanna go is free, if not checking other places.
//Changing the person coordinates
    }
