#ifndef JUEGO_H
#define JUEGO_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Mapa.h"
#include "Jugador.h"

class Juego
{
    public:
        bool moviendo;
        char direccion;
        Mapa* mapa;
        Jugador* jugador1;
        int xMapa, yMapa;
        static const int WIDTH = 640;
        static const int HEIGHT = 480;
        TTF_Font *font = NULL;
        Juego();
        virtual ~Juego();

        void moverCamara();
        void logica();
        void render();
        void eventos(SDL_Event* evento);
        SDL_Surface* getScreen();
    protected:
    private:
        SDL_Surface* screen, *background, *text;
        SDL_Rect camara;
};

#endif // JUEGO_H
