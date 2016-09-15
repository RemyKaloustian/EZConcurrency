/*
Author Matthieu BERGER
15/09/2016

EZConcurrency Project
*/

#include <stdio.h>


#define DEFAULT_GRID_WIDTH              128
#define DEFAULT_GRID_HEIGHT             32
#define DEFAULT_WALL_WIDTH              4


typedef enum {
    EMPTY, 
    WALL, 
    PERSON
} case_content_type;

