
/*
* Sport Game's : Who will be the first ?
* using property of synchronisation according to
* the concurrence
*
* author : @CésarCollé and @RemyKaloustian
* 25 / 09 / 2016
*
***/
#include <getopt.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/time.h>
//#include <SDL2/SDL.h> //need to install sdl : sudo apt-get install libsdl2-dev
#include "../inc/elements.h"
#include "../inc/launcher_version.h"
#include "../inc/designer.h"

#ifdef UI
#include "../inc/UITools.h"
#endif

// we assume to put opt script on Main function like other Linux's program do.
/*we need pointer, because arguments for function are by copy in C */
/*we will loose space&time without pointer */
#define VERSION_MAX 2



struct timeval time_start;
struct timeval time_end;

double get_user_time(){
    struct timeval time;
    if (gettimeofday(&time, NULL)){
        fprintf(stderr, "erreur calcul user time \n");
    }
    return (double) ((double)time.tv_sec + (double) time.tv_usec );
}


//Debug of negative values

struct timeval _start;
struct timeval _end;

// Manage opt given by user.
int
main(int argc, char *argv[]) {

  //SDL_Init
#ifdef UI
    UI_Init();
#endif

    struct execution execut = {0, 0, 0, 0, 0};
    time_start.tv_usec = 0;
    time_end.tv_usec = 0;
    /* iteration on argv with utilisation of get_opt library */
// the map structure
    grid map;
// value for the mesures.
    time_t t_begin = clock();
    double start,  duration;

    char c = 0;
    start = get_user_time();
    // nb_threads filled by user with opt -p
    // initialisation de la grille
    gettimeofday(&time_start, NULL);
    init_grid(&map, DEFAULT_GRID_HEIGHT, DEFAULT_GRID_WIDTH);
   // affic_grid(&map);
    while ((c = getopt(argc, argv, "m::t:p:e:")) != -1) {
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

            case 'e':
            if (!optarg) {
                fprintf(stderr, "-e need a parameter !\n");
                exit(0);
            }
            int mode = atoi(optarg);
            if (mode >VERSION_MAX){perror("erreur saisie version");}
            execut.mode = mode;
            break;
            default:
                printf("%c is not an option \n", c);
                exit(2);
        }
    }
    //launch a version with the -t command given by the user
    #ifdef DEBUG
    printf("mode : %d version : %d", execut.mode, execut.version);
    #endif
    launch_version(&execut, &map);
    free(map.population);
    // show time taken to the execution of the game.
    if (execut.show_time) {
        time_t t_end = clock();
        gettimeofday(&time_end, NULL);
        double time_ = (time_end.tv_sec*1e6 + time_end.tv_usec) - (time_start.tv_sec*1e6 + time_start.tv_usec);
        duration = (  ((double) get_user_time()) - start);
        #ifndef PLOT
        fprintf(stdout, "version :%d  people :%d  cpu :%f user :%f \n",execut.version, execut.nb_people,(float) ((t_end - t_begin)*1000)/CLOCKS_PER_SEC,time_/1000 );
        #else
        printf("%d %d %f %f \n",execut.version, execut.nb_people, (float) ((t_end - t_begin)*1000)/CLOCKS_PER_SEC ,time_/1000);
        #endif
    }
    //affic_grid(&map);
// fin options
    return 0;
}
