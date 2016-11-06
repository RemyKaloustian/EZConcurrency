#include <SDL2/SDL.h> //need to install sdl : sudo apt-get install libsdl2-dev

//Basic command to compile : gcc main.c -lSDL2-2.0
//Run : ./a.out

SDL_Window *mWindow;
SDL_Surface *mMainSurface;

int quit;
SDL_Event event;

const int Win_W = 512;
const int Win_H = 128;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} pixel;

void put_pixel(SDL_Surface* surf, int x,int y,pixel* p)
{
    Uint32* p_screen = (Uint32*)surf->pixels;
    p_screen += y*surf->w+x;
    *p_screen = SDL_MapRGBA(surf->format,p->r,p->g,p->b,p->a);
}

//Draws a wall
void draw_wall(pixel* wallpixel, int x_init, int x_limit, int y_init, int y_limit)
{
  for(int ix = x_init; ix < x_limit; ix++)
      for(int iy = y_init; iy < y_limit ; iy++)
      {
          put_pixel(mMainSurface, ix, iy, &wallpixel);
      }
}

void draw_person(pixel * person, int _x, int _y )
{
  for (size_t ix = _x; ix > _x-3; ix--)
  {
    for (size_t iy = _y; iy < _y+3; iy++)
    {
      put_pixel(mMainSurface, ix, iy, &person);
    }
  }
}

int main( int argc, char* args[] )
{
    pixel background;
    background.r = (Uint8)0xff;
    background.g = (Uint8)0xff;
    background.b = (Uint8)0xff;
    background.a = (Uint8)128;

    pixel wall;
    wall.r = (Uint8)0x0f;
    wall.g = (Uint8)0x30;
    wall.b = (Uint8)0x57;
    wall.a = (Uint8)128;

    pixel person;
    wall.r = (Uint8)0xff;
    wall.g = (Uint8)0xff;
    wall.b = (Uint8)0xff;
    wall.a = (Uint8)128;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return -1;
    }
    else
    {
        mWindow = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Win_W, Win_H, SDL_WINDOW_SHOWN );
        if( mWindow == NULL )
        {
            return -2;
        }
        else
        {
            mMainSurface = SDL_GetWindowSurface( mWindow );

            while (quit != 1)
            {
                SDL_LockSurface(mMainSurface);

                draw_wall(&wall,0,16,0,60);
                draw_wall(&wall,0,16,67,127);
                draw_wall(&wall,111,127,0,55);
                draw_wall(&wall,111,127,71,127 );

                draw_person(&person, 400,100);
                SDL_UnlockSurface(mMainSurface);

                SDL_UpdateWindowSurface( mWindow );
                if(SDL_PollEvent(&event)){
                	switch(event.type){
                		case SDL_QUIT:
                			quit = 1;
                			break;
                	}
                }
            }
        }
    }

    return 0;
}
