#ifndef UITOOLS_H
#define UITOOLS_H


#include <SDL2/SDL.h> //need to install sdl : sudo apt-get install libsdl2-dev
extern SDL_Window *mWindow;
extern SDL_Surface *mMainSurface;

extern int quit;
extern SDL_Event event;

extern const int Win_W ;
extern const int Win_H;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} pixel;

extern pixel background;
extern pixel wall;
extern pixel pixel_person;

//Dessine un pixel
void put_pixel(SDL_Surface* surf, int x,int y,pixel* p);


//Dessine un mur
void draw_wall(pixel* wallpixel, int x_init, int x_limit, int y_init, int y_limit);


//Dessine une personne
void UI_draw_person(pixel* person, int _x, int _y );


//Initialise les pixels
void init_pixels_because_ce_SDL_de_mes_couilles_veut_pas_le_faire_a_l_exterieur();


//Initialise la fenêtre
void UI_Init();

//Dessine les murs
void UI_draw_walls();


//Met à jour la fenêtre
void UI_update();

int is_wall(int x, int y);

//Recolorie les pixels en noir
void UI_reset();


#endif
