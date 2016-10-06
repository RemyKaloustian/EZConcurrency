#ifndef THREADING_PART_H
#define THREADING_PART_H

#include "../inc/launcher_version.h"

void create_single_thread(grid* map);
void create_threads(grid* );
void manage_partition(struct execution *, int );

#endif
