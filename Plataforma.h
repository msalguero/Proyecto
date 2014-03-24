#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>

using namespace std;

class Plataforma
{
    public:
        int posX, posY, width, height;
        string tipo;
        SDL_Surface* imagen;
        Plataforma();
        virtual ~Plataforma();

        virtual void mover() = 0;
        virtual void render(SDL_Surface* screen, int xMapa);
        string getTipo();
    protected:
    private:
};

#endif // PLATAFORMA_H
