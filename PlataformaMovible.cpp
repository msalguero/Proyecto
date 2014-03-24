#include "PlataformaMovible.h"

PlataformaMovible::PlataformaMovible(int x, int y, SDL_Surface* imagen)
{
    this->dir = -2;
    this->posX = x;
    this->posY = y;
    this->imagen = imagen;
    this->height = imagen->h;
    this->width = imagen->w;
    this->tipo = "Movible";

}

PlataformaMovible::~PlataformaMovible()
{

}

void PlataformaMovible::mover()
{
    posY+=dir;
    if(posY<100 || posY>400)
        dir = -dir;
}
