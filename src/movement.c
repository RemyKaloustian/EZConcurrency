#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MIN_FINAL_Y 60
#define MAX_FINAL_Y 67
#define NB_DIRECTION 3


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
        choice[0] = O;
        if ( (y - DEFAULT_GRID_HEIGHT / 2) < 0 ){
            choice[1] = S;
            choice[2] = SO;
        }
        else if ( ( y - DEFAULT_GRID_HEIGHT/2) > 0){
            choice[1] = N;
            choice[2] = NO;
        }
        else{
            choice[1] = O;
        }
    }
}

int is_done(person *persons, int nb) {
    for (int i = 0; i < nb; ++i) {
        if (persons[i].current_status == AVAILABLE) {
            return 1;
        }
    }
    return 0;
}

int check_done(grid * grid, person * p){
    if (p->x <= 15 ){
        p->current_status = DONE;
        printf("it's over for you \n");
        delete_entity(grid, p->x, p->y);
        //affic_grid(grid);
        return 1;
    }
    return 0;
}


void *automata_movement(void *param_ptr_data) {
    printf("AUTOMATA !! \n");
    struct movement *ptr_data = param_ptr_data;
    int cpt = 0;
    //going through the list of person
    printf("%d %d \n", ptr_data->ptr_grid->population[0].x, ptr_data->ptr_grid->population[1].x);

    while (is_done(ptr_data->ptr_grid->population, ptr_data->ptr_grid->people)) {
        for (int i = 0; i < ptr_data->ptr_grid->people; ++i) {
            printf("thread with bound  = %d %d %d %d ", ptr_data->left_bound, ptr_data->right_bound, ptr_data->top_bound, ptr_data->bottom_bound);
            if (is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)) {
                printf("process : %d %d cpt = %d\n", ptr_data->ptr_grid->population[i].x,ptr_data->ptr_grid->population[i].y, cpt);
                //Move the person
                //We need the ptr_date cuz we need to check the bounds and the spaces around the current person
                //We also need the person coordinates, so we pass the person

                if (ptr_data->ptr_grid->population[i].current_status != DONE){
                    move_person(ptr_data, &ptr_data->ptr_grid->population[i]);
                    printf("moved to  : %d %d \n", ptr_data->ptr_grid->population[i].x,ptr_data->ptr_grid->population[i].y);
                    if (!check_done(ptr_data->ptr_grid, &ptr_data->ptr_grid->population[i])) {

                        draw_entity(ptr_data->ptr_grid, ptr_data->ptr_grid->population[i].x,
                                    ptr_data->ptr_grid->population[i].y);
                    }
                }

                else{
                    printf("il a finis \n");
                }

            }
            else{
                printf("no process \n");
            }

        }
        //affic_grid(ptr_data->ptr_grid);
        if (cpt++ == 120){
            printf("end analys\n");
            break;
        }
    }
    //affic_grid(ptr_data->ptr_grid);
    printf("END AUTOMATE\n\n");
    return NULL;
}//automata_movement()

int is_in_bounds(person *current_person, struct movement *current_movement) {

    return current_person->x >= current_movement->left_bound && current_person->x <= current_movement->right_bound &&
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
        if (map->matrix[line][j].content != EMPTY) {
            return 0;
        }
    }
    return 1;
}

int check_up(grid *map, int x, int y) {
    if (y - 1 <= 0) {
        return 0;
    }
    printf("GO !\n");
    y = y -1;

    for (int j = x; j < x - DEFAULT_PEOPLE_SIZE; j--) {
        if (map->matrix[y][j].content !=  EMPTY) {
            return 0;

        }
    }

    return 1;
}

int check_left(grid *map, int x, int y) {
    x = x - DEFAULT_PEOPLE_SIZE;
    for (int j = y; j < y + DEFAULT_PEOPLE_SIZE; j++) {
        if (map->matrix[j][x].content != EMPTY) {
            return 0;
        }
    }
    return 1;
}

int check_up_left(grid *map, int x, int y) {
    int _y = y - 1;
    int _x = x - DEFAULT_PEOPLE_SIZE;
    if (y < 1)return 0;
    return (check_up(map, x, y) && check_left(map, x, y) && map->matrix[_y][_x].content == EMPTY);
}

int check_down_left(grid *map, int x, int y) {
    int _y = y + DEFAULT_PEOPLE_SIZE;
    int _x = x - DEFAULT_PEOPLE_SIZE;
    if (y < 1)return 0;
    return (check_up(map, x, y) && check_left(map, x, y) && map->matrix[_y][_x].content == EMPTY);
}


void move_person(struct movement *current_movement, person *current_person) {
    int i;
    enum Direction direction[NB_DIRECTION + 1];
    memset(direction, 0, NB_DIRECTION + 1);
    printf("\n");
    make_choice(direction, current_person);
    //TODO : fill the switch
    while (direction[i] != 0) {

        switch (direction[i++]) {
            case O:
                printf("direction = Ouest\n");
                if (check_left(current_movement->ptr_grid, current_person->x, current_person->y)) {
                    printf("take = Ouest\n");
                    delete_entity(current_movement->ptr_grid, current_person->x, current_person->y);
                    current_person->x--;
                    return;
                }
                break;

            case NO:
                printf("direction = NO\n");
                if (check_up_left(current_movement->ptr_grid, current_person->x, current_person->y)) {
                    printf("take = NO\n");
                    delete_entity(current_movement->ptr_grid, current_person->x, current_person->y);
                    current_person->x--;
                    current_person->y--;
                    return;
                }
                break;
            case SO:
                printf("direction = SO\n");

                if (check_down_left(current_movement->ptr_grid, current_person->x, current_person->y)) {
                    printf("take = SO\n");
                    delete_entity(current_movement->ptr_grid, current_person->x, current_person->y);
                    current_person->x--;
                    current_person->y++;
                    printf("SO ! \n");
                    return;
                }
                break;
            case N:
                printf("direction = N\n");

                if (check_up(current_movement->ptr_grid, current_person->x, current_person->y)) {
                    printf("take = N\n");
                    delete_entity(current_movement->ptr_grid, current_person->x, current_person->y);
                    current_person->y--;
                    printf("NORTH \n");
                    return;
                }
                break;
            case S:
                printf("direction = S\n");

                if (check_down(current_movement->ptr_grid, current_person->x, current_person->y)) {
                    printf("take = s\n");
                    delete_entity(current_movement->ptr_grid, current_person->x, current_person->y);
                    current_person->y++;
                    printf("Sud\n");
                    return;

                }
                break;
        }

    }

//First we check if the place we wanna go is free, if not checking other places.
//Changing the person coordinates
}

