#include "Plataforma.h"

Plataforma::Plataforma()
{
    posX = 0;
    posY = 0;
    width = 0;
    height = 0;
    imagen = NULL;
}

Plataforma::~Plataforma()
{
    SDL_FreeSurface(imagen);
}

void Plataforma::render(SDL_Surface* screen, int xMapa)
{
    SDL_Rect offset;

    offset.x = posX-xMapa;
    offset.y = posY;

    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 100;
    clip.h = 25;

    SDL_BlitSurface(imagen, &clip, screen, &offset);
}

string Plataforma::getTipo()
{
    return tipo;
}
