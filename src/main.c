#include <getopt.h>
#include <stdio.h>
#include <time.h>
#include "../inc/elements.h"



static struct option long_options[] = {
  {0, 0, 0, 0}
};


struct execution {
  int nb_threads;
  int version;
  int nb_peaple;
};

// we assume to put opt script on Main function like other Linux's program do.
  /*we need pointer, because arguments for function are by copy in C */
  /*we will loose space&time without pointer */
// Mange opt given by user.
int
main (int argc, char *argv[])
{
  struct execution;
  /* iteration on argv with utilisation of get_opt library */
  grid map;
  time_t t_begin;
  char c = 0;
  // nb_threads filled by user with opt -p
  int version;

  pthread_t * threads;
  // initialisation de la grille
  init_grid(map, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
  while ((c = getopt (argc, argv, "m:tp")) != -1){
    switch(c){
        case 'm':
            begin = clock();
            printf("mesure  ! \n");
            break;
        case 'p':
          // filling randomly the grid
            random_populate_grid(map,atoi(optarg) );
            printf("nombre de gens %s !\n", optarg);
            break;
        case 't':
          // create threads initialization
            version = atoi(optarg);
            (version > 1)?()
            pthread_t tmp_threads[nb_thread];
            threads = tmp_threads;
            printf("nombre de thread %s\n", optarg);
            break;
        default:
            printf("%c is not an option \n", c);
            exit(0);
            break;

    }

    for (size_t i = 0; i < nb_thread; i++) {
      pthread_create(threads[i], NULL, )
    }

  }
// fin options


  return 0;
}
