#ifndef MONITOR_H
#define MONITOR_H
#include <pthread.h>


struct monitor {
  void (*get)(struct monitor *);
  void (*release)(struct monitor*);
  pthread_mutex_t mutex_monitor;
};

void initialisation_moniteur(struct monitor * ptr_monitor);


#endif
