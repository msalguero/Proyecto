#ifndef BOMBA_H
#define BOMBA_H
#include "Enemigo.h"

class Bomba : public Enemigo
{
    public:
        bool explotar;
        Bomba(int x, int y,SDL_Surface* img);
        virtual ~Bomba();

        void mover(vector<Tile*> tiles, int xMapa, int yMapa);
        void mostrar(SDL_Surface* screen, int xMapa, int yMapa);
    protected:
    private:
        SDL_Rect clips[11];
};

#endif // BOMBA_H
