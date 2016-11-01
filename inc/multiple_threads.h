//
// Created by caesar on 10/7/16.
//

#ifndef EZCONCURRENCY_MULTIPLE_THREADS_C_H
#define EZCONCURRENCY_MULTIPLE_THREADS_C_H
#include "../inc/elements.h"

struct multiple_movement{
    grid * map;
    int rank;
};



void * multiple_movement(void*);

void * multple_synchronized_sem(void * data);
#endif //EZCONCURRENCY_MULTIPLE_THREADS_C_H
