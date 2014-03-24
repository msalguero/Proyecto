#ifndef JUGADOR_H
#define JUGADOR_H
#include "Padre.h"
#include "Plataforma.h"
#include "PlataformaInvisible.h"
#include "Enemigo.h"
#include "Bomba.h"

class Jugador : public Padre
{
    public:
        int xvel, yvel, xacc, yacc, xCamara, yCamara, cVel, cVel2;
        bool suelo, saltando, colD, moviendo;
        Jugador();
        virtual ~Jugador();
        void mostrar(SDL_Surface* screen, int xMapa, int yMapa);
        void mover(vector<Enemigo*> enemigos, vector<Plataforma*> plataformas, vector<Tile*> tiles, int xMapa, int yMapa, Sint16* Camara, int *xMap);
        void saltar();
        void setMoviendo(bool b);
        void setFrame(char direction);
    protected:
    private:
        static const int sprites = 10;
        SDL_Rect clips[sprites];
        double frame;
};

#endif // JUGADOR_H
