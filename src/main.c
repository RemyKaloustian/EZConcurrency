#include <getopt.h>
#include <stdio.h>




static struct option long_options[] = {
  {0, 0, 0, 0}
};


// we assume to put opt script on Main function like other Linux's program do.

  /*we need pointer, because arguments for function are by copy in C */
  /*we will loose space&time without pointer */



// Mange opt given by user.
int
main (int argc, char *argv[])
{
  /* iteration on argv with utilisation of get_opt library */
  struct execut
  {
    int nb_thread;

  } executing;
  char c = 0;
  while ((c = getopt (argc, argv, "m:tp")) != -1){
    switch(c){
        case 'm':
            printf("mesure  ! \n");
            break;
        case 'p':
            printf("nombre de gens %s !\n", optarg);
            break;
        case 't':
            printf("nombre de thread %s\n", optarg);
            break;
        default:
            printf("%c is not an option \n", c);
            break;
    
    }
  
  }
  return 0;
}
