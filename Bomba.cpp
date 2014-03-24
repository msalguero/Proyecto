#include "Bomba.h"

Bomba::Bomba(int x, int y,SDL_Surface* img)
{
    tipo = 0;
    colision = false;
    frame = 0;
    coordX = x;
    coordY = y;
    this->imagen = img;
    this->height = 40;
    this->width = 40;
    xvel = 2;
    yvel = 2;
    explotar = false;
    for(int i = 0; i<9; i++)
    {
        clips[i].y = 0;
        clips[i].x = i*46;
        clips[i].h = 50;
        clips[i].w = 50;
    }
        clips[9].y = 0;
        clips[9].x = 407;
        clips[9].h = 50;
        clips[9].w = 50;
        clips[10].y = 0;
        clips[10].x = 457;
        clips[10].h = 50;
        clips[10].w = 50;
}

Bomba::~Bomba()
{
    //dtor
}

void Bomba::mover(vector<Tile*> tiles, int xMapa, int yMapa)
{
    if(explotar)
    {
        xvel = 0;
        return ;
    }
    colision = false;
    for(int i = 0; i<tiles.size(); i++)
    {
//        if(tiles[i]->tipo == 0 || !enPantalla(tiles[i]->x, tiles[i]->y, xMapa, yMapa))
//            continue;
        if(colisionBasica(coordX, coordY, tiles[i]->x, tiles[i]->y))
            {

                colision = true;

                if(coordX+40>tiles[i]->x && coordX+40<tiles[i]->x+50 && coordY == tiles[i]->y+12)
                    xvel = -2;
                else if(coordX<tiles[i]->x+50 && coordX>tiles[i]->x && coordY == tiles[i]->y+12)
                    xvel = 2;
            }
    }
    if(colision)
        yvel = 0;
    else
        yvel = 2;
     coordX+=xvel;
     coordY+=yvel;
}
void Bomba::mostrar(SDL_Surface* screen, int xMapa, int yMapa)
{
    SDL_Rect offset;

    offset.x = coordX-xMapa;
    offset.y = coordY;
    if(xvel > 0)
    {
        frame+=0.2;
        if(frame>5.9 || frame <3)
            frame = 3;
    }
    if(xvel < 0)
    {
        frame+=0.2;
        if(frame>2.9 || frame < 0)
            frame = 0;
    }
    if(explotar)
    {
        frame+=0.3;
        if(frame < 5.9)
            frame = 6;
    }
    SDL_BlitSurface(imagen, &clips[(int)frame], screen, &offset);
}
