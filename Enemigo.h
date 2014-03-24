#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Padre.h"

class Enemigo : public Padre
{
    public:
        int tipo;
        bool colision;
        double frame;
        int height, width;
        int yvel, xvel;
        Enemigo();
        virtual ~Enemigo();

        virtual void mover(vector<Tile*> tiles, int xMapa, int yMapa) = 0;
        virtual void mostrar(SDL_Surface* screen, int xMapa, int yMapa);
    protected:
    private:
};

#endif // ENEMIGO_H
