/*
* Sport Game's : Who will be the first ?
* using property of synchronisation according to
* the concurrence
*
*
***/



#include <getopt.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../inc/elements.h"
#include "../inc/launcher_version.h"

//#define REMYBG

// we assume to put opt script on Main function like other Linux's program do.
/*we need pointer, because arguments for function are by copy in C */
/*we will loose space&time without pointer */
// Manage opt given by user.
int
main(int argc, char *argv[]) {
    struct execution execut = {0, 0, 0, 0};
    /* iteration on argv with utilisation of get_opt library */
    grid map;
    time_t t_begin;
    char c = 0;
    // nb_threads filled by user with opt -p
    // initialisation de la grille
    init_grid(&map, DEFAULT_GRID_HEIGHT, DEFAULT_GRID_WIDTH);
   // affic_grid(&map);

    while ((c = getopt(argc, argv, "mt:p:")) != -1) {
        switch (c) {
            case 'm':
                t_begin = clock();
                execut.show_time = 1;
                printf("mesure  ! \n");
                break;
            case 'p':
                // filling randomly the grid
               // random_populate_grid(&map, atoi(optarg));
                printf("-p OK \n");
                random_populate_grid(&map, 2);
                execut.nb_people = 2; //pow (2, atoi (optarg));
                if (!optarg) {
                    fprintf(stderr, "-p need a parameter !\n");
                    exit(0);
                }
                printf("nombre de gens %s !\n", optarg);
                break;
            case 't':
                // create threads initialization
                printf("optarg = %s\n", optarg);
                if (!optarg) {
                    fprintf(stderr, "-t need a parameter !\n");
                    exit(0);
                }
                execut.version = atoi(optarg);
                printf("nombre de thread %s\n", optarg);
                break;
            default:
                printf("%c is not an option \n", c);
                exit(0);
                break;
        }
    }
    //launch a version with the -t command given by the user
    printf("out of switch main \n");
    launch_version(&execut, &map);
    // show time taken to the execution of the game.
    if (execut.show_time) {
        time_t t_end = clock();
        printf("time : %f \n", (float) (t_end - t_begin) / CLOCKS_PER_SEC);
    }
// fin options
    return 0;
}
