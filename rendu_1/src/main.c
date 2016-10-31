
/*
* Sport Game's : Who will be the first ?
* using property of synchronisation according to
* the concurrence
*
* author : @CésarCollé and @RemyKaloustian
* 25 / 09 / 2016
*
***/
//#include <bits/time.h>
#include <getopt.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/designer.h"

// we assume to put opt script on Main function like other Linux's program do.
/*we need pointer, because arguments for function are by copy in C */
/*we will loose space&time without pointer */
#define VERSION_MAX 2
double get_user_time(){
    struct timeval time;
    if (gettimeofday(&time, NULL)){
        fprintf(stderr, "erreur calcul user time \n");
    }
    return (double) time.tv_sec + (double) time.tv_usec * 0.000001;
}

// Manage opt given by user.
int
main(int argc, char *argv[]) {
    struct execution execut = {0, 0, 0, 0};
    /* iteration on argv with utilisation of get_opt library */
// the map structure
    grid map;
// value for the mesures.
    time_t t_begin;
    double start,  duration;

    char c = 0;
    start = get_user_time();
    // nb_threads filled by user with opt -p
    // initialisation de la grille
    init_grid(&map, DEFAULT_GRID_HEIGHT, DEFAULT_GRID_WIDTH);
   // affic_grid(&map);

    while ((c = getopt(argc, argv, "mt:p:")) != -1) {
        switch (c) {
            case 'm':
                t_begin = clock();
                execut.show_time = 1;
                break;
            case 'p':
                // filling randomly the grid
                execut.nb_people = pow (2, atoi (optarg));
                random_populate_grid(&map, execut.nb_people);

                if (!optarg) {
                    fprintf(stderr, "-p need a parameter !\n");
                    exit(0);
                }
                break;
            case 't':
                // create threads initialization
                if (!optarg) {
                    fprintf(stderr, "-t need a parameter !\n");
                    exit(0);
                }
                int version = atoi(optarg);

                if (version >VERSION_MAX){perror("erreur saisie version");}
                execut.version = version;
                break;
            default:
                printf("%c is not an option \n", c);
                exit(2);
        }
    }
    //launch a version with the -t command given by the user
    launch_version(&execut, &map);
    free(map.population);
    // show time taken to the execution of the game.
    if (execut.show_time) {
        time_t t_end = clock();
        duration = get_user_time() - start;
        fprintf(stdout, "mode : %d  people :%d  CPU :%f ms USER :%f ms \n",execut.version, execut.nb_people, (float) ((t_end - t_begin)*1000)/CLOCKS_PER_SEC , duration*1000);
    }
// fin options
    return 0;
}
