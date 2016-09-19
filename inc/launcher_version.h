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
  int nb_peaple;
  int show_time;
};

void launch_version(struct execution *, grid *);

#endif
