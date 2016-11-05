#include <SDL2/SDL.h> //need to install sdl : sudo apt-get install libsdl2-dev

//Basic command to compile : gcc main.c -lSDL2-2.0
//Run : ./a.out

SDL_Window *mWindow;
SDL_Surface *mMainSurface;

int quit;
SDL_Event event;
//SDL_PollEvent(&event);

const int Win_W = 512   ;
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

void draw_left_upper_wall(pixel * wallpixel)
{
  for(int ix = 0; ix < 16; ix++)
      for(int iy = 0; iy < 60 ; iy++)
      {
          put_pixel(mMainSurface, ix, iy, &wallpixel);
      }
}

void draw_left_lower_wall(pixel * wallpixel)
{
  for(int ix = 0; ix < 16; ix++)
      for(int iy = 68; iy < 127 ; iy++)
      {
          put_pixel(mMainSurface, ix, iy, &wallpixel);
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
    wall.r = (Uint8)0xf;
    wall.g = (Uint8)0x30;
    wall.b = (Uint8)0x57;
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

                draw_left_upper_wall(&wall);
                draw_left_lower_wall(&wall);


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
