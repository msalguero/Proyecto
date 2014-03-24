#include "PlataformaInvisible.h"

PlataformaInvisible::PlataformaInvisible(int x, int y, SDL_Surface* imagen)
{
    cont = 0;
    roto = false;
    this->posX = x;
    this->posY = yOrigin = y;
    this->imagen = imagen;
    this->height = imagen->h;
    this->width = imagen->w;
    this->tipo = "Invisible";
    int cont2 = 0;
    pos = 0;
    for(int i = 0; i<5 ; i++)
    {
        clips[cont2].x = 0;
        clips[cont2].y = (i * 26);
        clips[cont2].h = 25;
        clips[cont2++].w = 100;
    }
    clips[3].h = 50;
    clips[4].y = clips[3].h + 75;;
    clips[4].h = 88;
}

PlataformaInvisible::~PlataformaInvisible()
{
    //dtor
}
void PlataformaInvisible::mover()
{
    romper();
    if(roto)
    {
        posY++;
        pos++;
        cont--;
    }
}

void PlataformaInvisible::contar()
{
    cont++;
}

void PlataformaInvisible::render(SDL_Surface* screen, int xMapa)
{
    SDL_Rect offset;

    offset.x = posX-xMapa;
    offset.y = posY;

    int clip = 0;
    if(pos < 5)
        clip = 2;
    else if(pos<10)
        clip = 3;
    else if(pos<15)
        clip = 4;
    else
        clip = 6;
    if(roto == false)
        if(cont>20)
            clip = 1;
        else
            clip = 0;
    SDL_BlitSurface(imagen, &clips[clip], screen, &offset);
}

bool PlataformaInvisible::romper()
{
    if(cont>40)
        roto = true;
    if(cont == -30)
    {
        roto = false;
        posY = yOrigin;
        pos = 0;
        cont = 0;
    }
}
