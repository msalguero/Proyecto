#include "Planta.h"

Planta::Planta(int x, int y, SDL_Surface* img)
{
    frame = 0;
    tipo = 1;
    coordX = x;
    coordY = y;
    for(int i = 0; i<2; i++)
    {
        clips[i].y = 0;
        clips[i].x = i*50;
        clips[i].h = 100;
        clips[i].w = 50;
    }
    imagen = img;
}

Planta::~Planta()
{
    //dtor
}

void Planta::mover(vector<Tile*> tiles, int xMapa, int yMapa)
{

}

void Planta::mostrar(SDL_Surface* screen, int xMapa, int yMapa)
{
    SDL_Rect offset;

    offset.x = coordX-xMapa;
    offset.y = coordY;

    frame+=0.1;
    if(frame>1.9)
        frame = 0;

    SDL_BlitSurface(imagen, &clips[(int)frame], screen, &offset);
}
