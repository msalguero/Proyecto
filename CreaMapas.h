#ifndef CREAMAPAS_H
#define CREAMAPAS_H
#include "Mapa.h"
#include "Padre.h"
#include "Plataforma.h"
#include "PlataformaMovible.h"
#include "PlataformaInvisible.h"
#include "Enemigo.h"
#include "Bomba.h"
#include "Planta.h"
#include "Tile.h"

class CreaMapas
{
    public:
        int xMapa, yMapa;
        int vel, seleccion;
        static const int WIDTH = 50;
        static const int HEIGHT = 11;
        int mapa[HEIGHT][WIDTH];
        SDL_Surface* screen, *background, *source;
        SDL_Rect camara;

        CreaMapas(SDL_Surface* screen);
        virtual ~CreaMapas();

        void loop();
        void render();
        void applySurface(int x, int y, SDL_Rect* clip);
        void escribirMapa();
        void eventos(SDL_Event* evento);
        void moverCamara();
    protected:
    private:
        bool puntoEstaDentroDeCaja(int p_x,int p_y,int c_x,int c_y,int c_h,int c_w);
};

#endif // CREAMAPAS_H
