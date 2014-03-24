#ifndef MENU_H
#define MENU_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <fstream>

using namespace std;

//seleccion 1 jugar
//seleccion 2 score
//seleccion 3 instrucciones
class Menu
{
    public:
        int seleccion;
        bool terminar, instr, score;
        string names[3];
        int scores[3];
        SDL_Surface *background;
        SDL_Surface *instrucciones;
        SDL_Surface *botones;
        SDL_Surface *screen;
        TTF_Font *font = NULL;
        Menu(SDL_Surface* sc);
        virtual ~Menu();

        void render();
        void eventos(SDL_Event* evento);
    protected:
    private:
        void applySurface(int x, int y, SDL_Surface* imagen, SDL_Rect *clip=NULL);
        void leerScore();
        SDL_Rect clips[8];
};

#endif // MENU_H
