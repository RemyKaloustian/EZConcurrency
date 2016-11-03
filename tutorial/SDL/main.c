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

int main( int argc, char* args[] )
{
    pixel mpixel;
    mpixel.r = (Uint8)0x00;
    mpixel.g = (Uint8)0xff;
    mpixel.b = (Uint8)0xff;
    mpixel.a = (Uint8)128;

    pixel ppixel;
    ppixel.r = (Uint8)0x00;
    ppixel.g = (Uint8)0xff;
    ppixel.b = (Uint8)0x00;
    ppixel.a = (Uint8)128;

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

                for(int ix = 0; ix < Win_W; ix++)
                    for(int iy = 0; iy < Win_H; iy++)
                    {
                      if(iy < 50)
                        put_pixel(mMainSurface, ix, iy, &mpixel);
                      else
                        put_pixel(mMainSurface, ix, iy, &ppixel);

                    }



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
