//
// Created by caesar on 10/8/16.
//
#include "../inc/elements.h"

// function needed for the GUI. we draw the square associate to an element.
void draw_entity(grid *map, int x, int y) {
    for (int i = y; i < y + DEFAULT_PEOPLE_SIZE; i++) {
        for (int j = x; j > x - DEFAULT_PEOPLE_SIZE; j--) {
            map->matrix[i][j].content = PERSON;
        }

    }
}

void delete_entity(grid *map, int x, int y) {
    for (int i = y; i < y + DEFAULT_PEOPLE_SIZE; i++) {
        for (int j = x; j > x - DEFAULT_PEOPLE_SIZE; j--) {
            map->matrix[i][j].content = EMPTY;
        }

    }
}


void affic_grid(grid *map) {
    for (size_t i = 0; i < DEFAULT_GRID_HEIGHT; i++) {
        for (size_t j = 0; j < DEFAULT_GRID_WIDTH; j++) {
            switch (map->matrix[i][j].content) {
                case EMPTY:
                    putchar('-');
                    break;
                case WALL:
                    putchar('|');
                    break;
                case PERSON:
                    putchar('x');
                    break;
                default :
                    exit(1);
            }
        }
    }
}
