#ifndef PLATAFORMAMOVIBLE_H
#define PLATAFORMAMOVIBLE_H
#include "Plataforma.h"


class PlataformaMovible : public Plataforma
{
    public:
        int dir;
        PlataformaMovible(int x, int y, SDL_Surface* imagen);
        virtual ~PlataformaMovible();

        void mover();
    protected:
    private:
};

#endif // PLATAFORMAMOVIBLE_H
