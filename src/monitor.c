#include "../inc/monitor.h"
#include <pthread.h>
#include <stdio.h>

int ticket = 1;
pthread_cond_t signal_release;


void get(struct monitor * ptr_monitor){
    pthread_mutex_lock(&ptr_monitor->mutex_monitor);
    while (ticket < 1 ){
      pthread_cond_wait(&signal_release, &ptr_monitor->mutex_monitor);
    }
    ticket--;
  pthread_mutex_unlock(&ptr_monitor->mutex_monitor);
}


void release(struct monitor * ptr_monitor){
  ticket++;
  pthread_cond_signal(&signal_release);
}



void initialisation_moniteur(struct monitor * ptr){
  ptr->mutex_monitor=(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  ptr->get = get;
  ptr->release = release;
  pthread_cond_init(&signal_release, 0);
}

void destroy_monitor(struct monitor *ptr_monitor){
  pthread_mutex_destroy(&(ptr_monitor->mutex_monitor));
  pthread_cond_destroy(&signal_release);
}
