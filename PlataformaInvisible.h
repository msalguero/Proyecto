#ifndef PLATAFORMAINVISIBLE_H
#define PLATAFORMAINVISIBLE_H
#include "Plataforma.h"

class PlataformaInvisible : public Plataforma
{
    public:
        int cont, pos, yOrigin;
        bool roto;
        SDL_Rect clips[5];
        PlataformaInvisible(int x, int y, SDL_Surface* imagen);
        virtual ~PlataformaInvisible();

        void mover();
        void contar();
        bool romper();
        void render(SDL_Surface* screen, int xMapa);
    protected:
    private:
};

#endif // PLATAFORMAINVISIBLE_H
