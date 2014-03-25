#ifndef MAPA_H
#define MAPA_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Plataforma.h"
#include "PlataformaMovible.h"
#include "PlataformaInvisible.h"
#include "Enemigo.h"
#include "Planta.h"
#include "Bomba.h"
#include "Tile.h"
#include "Padre.h"

using namespace std;

class Mapa : public Padre
{
    public:
        vector<Tile*> tiles;
        vector<Plataforma*> plataformas;
        vector<Enemigo*> enemigos;
        int height;
        int width;
        SDL_Surface* imagen, *IMGplataformas[2], *ambiente, *enemigoIMG[2], *imgTorre;
        Mapa(int h,int w);
        virtual ~Mapa();

        void crear(char* File);
        void render(SDL_Surface* screen, int xMapa, int yMapa);
    protected:
    private:
        void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, int tipoT);
};

#endif // MAPA_H
