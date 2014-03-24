#ifndef PLANTA_H
#define PLANTA_H
#include "Enemigo.h"


class Planta : public Enemigo
{
    public:
        Planta(int x, int y, SDL_Surface* img);
        virtual ~Planta();

        void mover(vector<Tile*> tiles, int xMapa, int yMapa);
        void mostrar(SDL_Surface* screen, int xMapa, int yMapa);
    protected:
    private:
        SDL_Rect clips[2];
};

#endif // PLANTA_H
