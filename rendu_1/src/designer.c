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
    int cpt = 0;
    for (size_t i = 0; i < DEFAULT_GRID_HEIGHT; i++) {
        cpt++;
        for (size_t j = 0; j < DEFAULT_GRID_WIDTH; j++) {
            cpt++;
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
                    fprintf(stderr, "whaaaat?  \n");
            }
            //printf("nombre de ligne : %d\n", cpt/DEFAULT_GRID_WIDTH);
        }
        printf("\n");
    }
    printf("j'ai afficher : %d elements \n", cpt);
}
