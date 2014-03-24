#ifndef PADRE_H
#define PADRE_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tile.h"
#include <vector>

using namespace std;

class Padre
{
    public:
        static const int TILE_SIZE = 50;
        static const int WIDTH_SCREEN = 640;
        static const int HEIGHT_SCREEN = 480;
        int coordX, coordY;
        SDL_Surface* imagen;
        Padre();
        virtual ~Padre();

        virtual void mover(vector<Tile*> tiles){}
        virtual void mostrar(SDL_Surface* screen, int xMapa, int yMapa){}
        bool enPantalla(int xObjeto, int yObjeto, int x1, int y1);
        bool colisionBasica(int personaje_x,int personaje_y,int enemigo_x,int enemigo_y, int width = TILE_SIZE, int height = TILE_SIZE);
        vector<Tile*> getTiles(int xIn,int yIn,int xFin,int yFin, vector<Tile*> tiles);
    protected:
        bool puntoEstaDentroDeCaja(int p_x,int p_y,int c_x,int c_y,int c_h,int c_w);
    private:

};

#endif // PADRE_H
