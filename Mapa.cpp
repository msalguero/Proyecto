#include "Mapa.h"

Mapa::Mapa(int h,int w)
{
    height = h;
    width = w;
    IMGplataformas[0] = IMG_Load("Plataformas.png");
    IMGplataformas[1] = IMG_Load("PlataformaRompible.png");
    imagen = IMG_Load("Tiles.png");
    enemigoIMG[0] = IMG_Load("Planta.png");
    enemigoIMG[1] = IMG_Load("Bomba.png");
}

Mapa::~Mapa()
{
    SDL_FreeSurface(imagen);
    for(int i = 0; i<2; i++)
    {
        SDL_FreeSurface(IMGplataformas[i]);
        SDL_FreeSurface(enemigoIMG[i]);
    }
}

void Mapa::render(SDL_Surface* screen, int xMapa, int yMapa)
{
    int cont = 0;
    for(int i = 0; i<height; i++)
        for(int k = 0; k<width; k++)
        {
        if(tiles[cont]->tipo != 0 && enPantalla(tiles[cont]->x, tiles[cont]->y, xMapa, yMapa))
        {
             applySurface(tiles[cont]->x - xMapa, tiles[cont]->y , imagen, screen, tiles[cont]->tipo);
        }
        cont++;
        }
    for(int i = 0; i<plataformas.size(); i++)
    {
        plataformas[i]->mover();
        if(enPantalla(plataformas[i]->posX, plataformas[i]->posY, xMapa, yMapa))
            plataformas[i]->render(screen, xMapa);
    }
     for(int i = 0; i<enemigos.size(); i++)
    {
        enemigos[i]->mover(tiles, xMapa, yMapa);
        enemigos[i]->mostrar(screen, xMapa, yMapa);

        if(enemigos[i]->frame>10.1)
        {
            delete enemigos[i];
            enemigos.erase(enemigos.begin()+i);
        }
    }
}

void Mapa::applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, int tipoT)
{
     //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    SDL_Rect clip;
    clip.x = (tipoT-1)*50;
    clip.y = 0;
    clip.w = clip.h = 50;

    SDL_BlitSurface( source, &clip, destination, &offset );
}

void Mapa::crear(char* File)
{
     ifstream in(File);
    if(in == NULL)
        exit(0);
     for(int i = 0; i<height; i++)
        for(int k = 0; k<width; k++)
        {
            int tipo = 0;
            in>>tipo;
            if(tipo == 5)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                tiles.push_back(new Tile(0, 0, 0));
                enemigos.push_back(new Bomba(xCoor, yCoor, enemigoIMG[1]));
            }
            else if(tipo == 6)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                tiles.push_back(new Tile(0, 0, 0));
                enemigos.push_back(new Planta(xCoor, yCoor, enemigoIMG[0]));
            }
            else if(tipo == 9)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                tiles.push_back(new Tile(0, 0, 0));
                plataformas.push_back(new PlataformaMovible(xCoor, yCoor, IMGplataformas[1]));
            }else if(tipo == 8)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                tiles.push_back(new Tile(0, 0, 0));
                plataformas.push_back(new PlataformaInvisible(xCoor, yCoor, IMGplataformas[1]));
            }
            else if(tipo == 0)
                tiles.push_back(new Tile(0, 0, 0));
            else
            {
                int xCoor = k*50;
                int yCoor = i*50;
                tiles.push_back(new Tile(xCoor, yCoor, tipo));
            }
            cout << tipo;
        }
    in.close();
}
