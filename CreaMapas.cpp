#include "CreaMapas.h"

CreaMapas::CreaMapas(SDL_Surface* screen)
{
    this->screen = screen;
    background = IMG_Load("endless.png");
    source = IMG_Load("Objetos.png");
    camara.w = 640;
    camara.h = 500;
    for(int h = 0; h<HEIGHT; h++)
        for(int w = 0; w<WIDTH; w++)
        {
            mapa[h][w] = 0;
        }
}

CreaMapas::~CreaMapas()
{
    //dtor
}

void CreaMapas::render()
{
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    SDL_BlitSurface(background, &camara, screen, NULL);
    for(int i = 0; i<HEIGHT; i++)
        for(int k = 0; k<WIDTH; k++)
        {
            if(mapa[i][k] == 6)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = (mapa[i][k])*50;
                clip.y = 0;
                clip.w = 50;
                clip.h = 100;
                applySurface(xCoor, yCoor, &clip);
            }
            else if(mapa[i][k] == 9)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 0;
                clip.y = 50;
                clip.w = 100;
                clip.h = 50;
                applySurface(xCoor, yCoor, &clip);
//                tiles.push_back(new Tile(0, 0, 0));
//                plataformas.push_back(new PlataformaMovible(xCoor, yCoor, IMGplataformas[1]));
            }else if(mapa[i][k] == 8)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 120;
                clip.y = 50;
                clip.w = 100;
                clip.h = 50;
                applySurface(xCoor, yCoor, &clip);
//                tiles.push_back(new Tile(0, 0, 0));
//                plataformas.push_back(new PlataformaInvisible(xCoor, yCoor, IMGplataformas[1]));
            }
            else
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = (mapa[i][k])*50;
                clip.y = 0;
                clip.w = clip.h = 50;
                applySurface(xCoor, yCoor, &clip);
            }
        }
}

void CreaMapas::applySurface(int x, int y, SDL_Rect* clip)
{
     //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, screen, &offset );
}

void CreaMapas::loop()
{
    bool running = true;
    while(running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT :
                    running = false;
            }
        }
        render();

        SDL_Flip(screen);
    }
}
