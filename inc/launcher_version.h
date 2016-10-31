/**
*
*Launch the version given by user.
* according by the option -t given by user too.
*
* author : @CésarCollé
* 19 / 09 / 2016
**/


#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "../inc/elements.h"

struct execution {
  int nb_threads;
  int version;
  int nb_people;
  int show_time;
  int mode;
};
void launch_version(struct execution *ptr_execut, grid *map);
void launcher_all(struct execution *ptr_execut, grid * map);

#endif
