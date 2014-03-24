#include "Enemigo.h"

Enemigo::Enemigo()
{

}

Enemigo::~Enemigo()
{

}
void Enemigo::mostrar(SDL_Surface* screen, int xMapa, int yMapa)
{

    SDL_Rect offset;

    offset.x = coordX-xMapa;
    offset.y = coordY;
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 50;
    clip.h = 50;

    SDL_BlitSurface(imagen, NULL, screen, &offset);
}
