#ifndef MONITO_H
#define MONITOR_H
#include <pthread.h>


struct monitor {
  void (*get)(struct monitor *);
  void (*release)(struct monitor*);
  pthread_mutex_t mutex_monitor;
};



#endif
