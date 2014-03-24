#include "SDL/SDL.h"
#include "Juego.h"
#include "Menu.h"
#include <iostream>

using namespace std;

int main( int argc, char* args[] )
{
    Uint32 start;
    Juego platform;
    Menu menu(platform.getScreen());
    bool running = true;
    while(running)
    {
        SDL_Event event;

        if(menu.terminar == false)
        {
            menu.render();
            while(SDL_PollEvent(&event))
            {
                menu.eventos(&event);
            }
            continue;
        }
        start = SDL_GetTicks();

        while(SDL_PollEvent(&event))
        {
            platform.eventos(&event);
             switch(event.type)
            {
            case SDL_QUIT :
                running = false;
            }

        }
        platform.logica();

        platform.render();
        if(1000/30>(SDL_GetTicks()-start))
        {
            SDL_Delay(1000/30-(SDL_GetTicks()-start));
        }
        //if(platform.gameOver)
            //menu.terminar = platform.restart;
    }
    return 0;
}
