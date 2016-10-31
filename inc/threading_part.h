// threading part header
//author @CésarCollé
// 20 / 09 / 2016
#ifndef THREADING_PART_H
#define THREADING_PART_H
#include "../inc/launcher_version.h"

#define MIDDLE {256, 64, PERSON}
/*
 * we define boundaries
 *
 * */
#define TOP_RIGHT_CORNER {{DEFAULT_GRID_WIDTH, 0}, MIDDLE}}
#define TOP_LEFT_CORNER {{0, DEFAULT_GRID_WIDTH}, MIDDLE}
#define BOTTOM_LEFT_CORNER {{DEFAULT_GRID_HEGHT, 0}}
#define BOTTOM_RIGHT_CORNER {{0, DEFAULT_GRID_HEIGHT}}
#define THREADS_MAX 4



struct bound {
    cell top_right;
    cell top_down;
};

void create_single_thread(grid* map, void*(*funct)(void*));
void create_threads(grid*, void*(*funct)(void*) );
void multiple_threads(grid * map, void*(*funct)(void*));

#endif
