#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/movement.h"
#include <string.h>

#define MIN_FINAL_Y 60
#define MAX_FINAL_Y 67
#define NB_DIRECTION 3

// TODO #define MAX_FINAL_X 16

enum Direction {
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
    }


}

void *automata_movement(void *param_ptr_data) {

    struct movement *ptr_data = param_ptr_data;

    //going through the list of person
    for (int i = 0; ptr_data->ptr_grid->population; ++i) {

//Checking if the person is within the bounds of the thread
        if (is_in_bounds(&ptr_data->ptr_grid->population[i], ptr_data)) {
            //Move the person
            //We need the ptr_date cuz we need to check the bounds and the spaces around the current person
            //We also need the person coordinates, so we pass the person
            move_person(ptr_data, &ptr_data->ptr_grid->population[i]);


        }
    }
    return NULL;
}//automata_movement()

int is_in_bounds(person *current_person, struct movement *current_movement) {

    return current_person->x > current_movement->left_bound && current_person->x < current_movement->right_bound &&
           current_person->y > current_movement->top_bound && current_person->y < current_movement->bottom_bound;
    //The person is on the right chunk of the map
}//is_in_bounds()

// preCondition : every person we move are not eligible to finish the game

int check_down(grid *map, int x, int y) {
    if (y + DEFAULT_PEOPLE_SIZE >= DEFAULT_GRID_HEIGHT) {
        return -1;
    }
    int line = y + DEFAULT_PEOPLE_SIZE;

    for (int j = x; j < x - DEFAULT_PEOPLE_SIZE; j--) {
        if (map->matrix[line][j].content) {
            return -1;
        }
    }
    return 1;
}

int check_up(grid *map, int x, int y) {
    if (y - 1 >= 0) {
        return -1;
    }
    for (int j = y; j < y - DEFAULT_PEOPLE_SIZE; j--) {
        if (map->matrix[x][j].content) {
            return -1;
        }
    }
    return 1;
}

int check_left(grid *map, int x, int y) {

    if (y - 1 >= 0) {
        return -1;
    }
    for (int j = y; j < y - DEFAULT_PEOPLE_SIZE; j--) {
        if (map->matrix[x][j].content) {
            return -1;
        }
    }
    return 1;
}


void move_person(struct movement *current_movement, person *current_person) {

//if(current_person->y<MIN_FINAL_Y){
//    if(check_down(current_movement->ptr_grid, current_person->x, current_person->y)){
//
//    }
//}
//
//else if(current_person->y > MAX_FINAL_Y){
//
//}
//
//else {
//
//}
    int i = 0;
    enum Direction direction[NB_DIRECTION + 1];
    memset(direction, 0, NB_DIRECTION + 1);
    make_choice(direction, current_person);
    //TODO : fill the switch
    while (*direction) {
        switch (*(direction + i)) {
            case O:
                break;
            case NO:
                break;
            case SO:
                break;
            case N:
                break;
            case S:
                break;
        }
    }

//First we check if the place we wanna go is free, if not checking other places.
//Changing the person coordinates
}//move_person()
