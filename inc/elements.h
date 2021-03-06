/*
Author Matthieu BERGER
Author @CésarColle
15/09/2016

EZConcurrency Project
*/
#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_GRID_WIDTH              512
#define DEFAULT_GRID_HEIGHT             128
#define DEFAULT_WALL_WIDTH              16
#define DEFAULT_EXIT_HEIGHT_WALL_1      8
#define DEFAULT_EXIT_HEIGHT_WALL_2      16
#define DEFAULT_WALL_1_X                0
#define DEFAULT_WALL_2_X                111
#define DEFAULT_PEOPLE_SIZE             4

enum status{
    DONE,
    AVAILABLE
};


//Cell content type enum
typedef enum {
    EMPTY,
    WALL,
    PERSON
} cell_content_type;

//Cell structure
typedef struct {
    int x;
    int y;
    cell_content_type content;
} cell;



//Person structure
typedef struct {
    int x;
    int y;
    int height;
    int width;
    enum status current_status ;
    int it_alive;
} person;


//Grid structure
typedef struct {
    int height;
    int width;
    cell matrix[DEFAULT_GRID_HEIGHT][DEFAULT_GRID_WIDTH];
    person * population;
    int people;
} grid;

void set_cell_content(cell* my_cell, cell_content_type content);
void init_cell(cell* my_cell, int x, int y, cell_content_type content);
void init_grid(grid* my_grid, int width, int height);
void add_cell_to_grid(grid* my_grid, int x, int y, cell my_cell);
void add_walls(grid* my_grid);
void random_populate_grid(grid* my_grid, int people);
#endif
