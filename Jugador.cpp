#include "Jugador.h"

Jugador::Jugador()
{
    xCamara = 30;
    coordX = 30;
    yCamara = 150;
    coordY = 150;
    xvel = 0;
    yvel = 0;
    xacc = 0;
    yacc = 5;
    cVel = 0;
    cVel2 = 0;
    suelo = false;
    saltando = false;
    colD = false;
    moviendo = false;
    imagen = IMG_Load("player.png");
    for(int i = 0; i<sprites ; i++)
    {
        clips[i].x = (i * 40)+35;
        clips[i].y = 6;
        clips[i].h = clips[i].w = 40;
    }
}

Jugador::~Jugador()
{
    //dtor
}

void Jugador::mostrar(SDL_Surface* screen, int xMapa, int yMapa)
{
    SDL_Rect offset;

    offset.x = xCamara;
    offset.y = yCamara;

    SDL_BlitSurface(imagen, &clips[(int)(frame+0.5)], screen, &offset);
}

void Jugador::mover(vector<Enemigo*> enemigos, vector<Plataforma*> plataformas, vector<Tile*> tiles, int xMapa, int yMapa, Sint16* Camara, int *xMap)
{
    bool colision = false;
    bool piso = false;
    if(enemigos.size() == 0)
        exit(0);
    for(int i = 0; i<enemigos.size(); i++)
    {
        if(!enPantalla(enemigos[i]->coordX, enemigos[i]->coordY, xMapa, yMapa))
            continue;
        if(colisionBasica(coordX, coordY, enemigos[i]->coordX, enemigos[i]->coordY, 40, 40))
            {
                if(yvel >0 && coordY+40>=enemigos[i]->coordY)
                {
                    saltando = true;
                    suelo = false;
                    coordY-=10;
                    yCamara-=10;
                    yvel = -18;
                    ((Bomba*)enemigos[i])->explotar = true;
                }
                else
                {

                }
            }
    }

    for(int i = 0; i<plataformas.size(); i++)
    {
        if(!enPantalla(plataformas[i]->posX, plataformas[i]->posY, xMapa, yMapa))
            continue;
        if(colisionBasica(coordX, coordY, plataformas[i]->posX, plataformas[i]->posY, 100, 25))
            {
                if(yvel >= 0 &&(coordY)<plataformas[i]->posY)
                {
                    if(plataformas[i]->getTipo() == "Invisible")
                    {
                        if(!((PlataformaInvisible*)plataformas[i])->roto)
                            ((PlataformaInvisible*)plataformas[i])->contar();
                        else
                            continue;
                    }
                    suelo = true;
                    saltando = false;
                    colision = true;
                    coordY = plataformas[i]->posY-37;
                    yCamara = plataformas[i]->posY-37;
                    yvel = 0;
                }
            }
    }

    for(int i = 0; i<tiles.size(); i++)
    {
        if(tiles[i]->tipo == 0 || !enPantalla(tiles[i]->x, tiles[i]->y, xMapa, yMapa))
            continue;
        if(colisionBasica(coordX, coordY, tiles[i]->x, tiles[i]->y))
            {
                colision = true;

                if(yvel<0)
                {
                    coordY = tiles[i]->y+50;
                    yCamara = tiles[i]->y+50;
                    yvel = 0;
                }else if(yvel>0)
                {
                    suelo = true;
                    saltando = false;
                    if(yvel!=0){
                    coordY = tiles[i]->y-35;
                    yCamara = tiles[i]->y-35;
                    }
                    yvel = 0;
                }
                if(coordX <= tiles[i]->x+50 && (coordY != tiles[i]->y-35) && coordX>tiles[i]->x)
                {
//                    coordX -=xvel;
//                    xCamara -=xvel;
                    if(xvel<0)
                    {
                    xvel = 0;
                    cVel = 0;
                    colD = true;
                    moviendo = false;
                    }
                    cVel2 = 0;
                }else if(coordX+imagen->w >= tiles[i]->x && (coordY != tiles[i]->y-35) && coordX<tiles[i]->x)
                {
//                    coordX -=xvel;
//                    xCamara -=xvel;
                    if(xvel>0)
                    {
                    xvel = 0;
                    cVel = 0;
                    colD = true;
                    moviendo = false;
                    }
                    cVel2 = 0;
                }else
                {
//                    cVel2= 2;
                    colD = false;
                }
            }

    }
    if(!colision)
    {
        suelo = false;
        colD = false;
    }
    if(!suelo && yvel <=5)
        {
            yvel++;
        }

    xCamara += cVel;
    coordX += xvel;
    coordY += yvel;
    yCamara += yvel;
    *Camara+= cVel2;
    *xMap += cVel2;
    for(int i = 0; i<sprites ; i++)
    {
        clips[i].x = (i * 40)+35;
        clips[i].y = 6;
        clips[i].h = clips[i].w = 40;
    }
}

void Jugador::saltar()
{
    if(!saltando && suelo)
    {
        saltando = true;
        suelo = false;
        coordY-=5;
        yCamara-=5;
        yvel = -18;
    }
}

void Jugador::setMoviendo(bool b)
{
    this->moviendo = b;
}

void Jugador::setFrame(char direction)
{
    frame += 0.3;

    if(saltando && direction == 'd')
        frame = 8;
    else if(saltando && direction == 'i')
        frame = 9;
    else if(direction == 'd' && (frame<1.5 || frame>3.4))
        if(moviendo)
            frame = 1.3;
        else
            frame = 0;
    else if(direction == 'i' && (frame<3.5 || frame > 6.4))
        if(moviendo)
            frame = 4;
        else
            frame = 7;

        if(!moviendo && !saltando)
            if(direction == 'd')
                frame = 0;
            else
                frame = 7;
}
