#include "Juego.h"


Juego::Juego()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    background = IMG_Load("endless.png");
    loseScreen = IMG_Load("gameOver.jpg");
    yMapa = xMapa = camara.x = camara.y = 0;
    camara.w = WIDTH;
    camara.h = HEIGHT;
    moviendo = false;
    gameOver = false;
    restart = false;
    direccion = 'r';
    mapa = new Mapa(11, 50);
    mapa->crear("demo.txt");
    jugador1 = new Jugador();
    font = TTF_OpenFont("SMB.ttf", 32);
}

Juego::~Juego()
{
    SDL_FreeSurface(background);
    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
}

void Juego::moverCamara()
{
    if(jugador1->colD)
             return;
    if(jugador1->moviendo && direccion == 'i')
    {

        jugador1->xvel=-2;
        if(jugador1->xCamara<150)
            {
                jugador1->cVel2 = -2;
                jugador1->cVel=0;
            }
        else if(jugador1->moviendo)
            jugador1->cVel=-2;

        if(camara.x<0)
            camara.x = 2688-WIDTH;
    }else if(jugador1->moviendo && direccion == 'd')
    {
        jugador1->xvel=2;
        if(jugador1->xCamara>400)
            {
                jugador1->cVel=0;
                jugador1->cVel2=2;
            }
        else if(jugador1->moviendo)
            jugador1->cVel=2;

        if(camara.x >= 2688-WIDTH)
            camara.x = 0;
    }else
    {
        jugador1->xvel = 0;
        jugador1->cVel = 0;
        jugador1->cVel2 = 0;
    }
}

void Juego::render()
{
    if(gameOver)
    {
        SDL_Rect offset;

        offset.x = -200;
        offset.y = -50;

        SDL_BlitSurface(loseScreen, NULL, screen, &offset);
        SDL_Flip(screen);
        return ;
    }
    SDL_BlitSurface(background, &camara, screen, NULL);
    mapa->render(screen, xMapa, yMapa);
    jugador1->mostrar(screen, xMapa, yMapa);

//    char c[10];
//    sprintf(c, "%d", jugador1->coordX);
//    sprintf(c, "%d", xMapa);
//    char c2[] = {'s','c','o','r','e'};
//    strcat(c2, c);
    std::stringstream strmSc;
    strmSc <<"Score: "<<xMapa;

    SDL_Color color = {0,0,0};
    SDL_Surface* text = TTF_RenderText_Solid(font, strmSc.str().c_str(), color);
    SDL_BlitSurface(text, NULL, screen, NULL);

    SDL_Flip(screen);
    SDL_FreeSurface(text);
}

void Juego::logica()
{
    jugador1->mover(mapa->enemigos, mapa->plataformas, mapa->tiles, xMapa, yMapa, &camara.x, &xMapa);
    jugador1->setFrame(direccion);
    gameOver = jugador1->gameOver;
    moverCamara();
}

void Juego::eventos(SDL_Event* evento)
{
    switch(evento->type)
    {
    case SDL_KEYDOWN :
        switch(evento->key.keysym.sym)
        {
        case SDLK_LEFT :
            direccion = 'i';
            moviendo = true;
            jugador1->setMoviendo(true);
            break;
        case SDLK_RIGHT :
            direccion = 'd';
            moviendo = true;
            jugador1->setMoviendo(true);
            break;
        case SDLK_SPACE :
            jugador1->saltar();
            break;
        case SDLK_RETURN :
            if(gameOver)
                restartGame();
            break;
        default :;
        }
        break;

    case SDL_KEYUP :
        switch(evento->key.keysym.sym)
        {
        case SDLK_LEFT :
            moviendo = false;
            jugador1->setMoviendo(false);
            break;
        case SDLK_RIGHT :
            moviendo = false;
            jugador1->setMoviendo(false);
            break;
        default :;
        }
        break;
    }
}

SDL_Surface* Juego::getScreen()
{
    return screen;
}

void Juego::restartGame()
{
    restart = true;
    delete mapa;
    delete jugador1;
    yMapa = xMapa = camara.x = camara.y = 0;
    moviendo = false;
    gameOver = false;
    direccion = 'r';
    mapa = new Mapa(11, 50);
    mapa->crear("demo.txt");
    jugador1 = new Jugador();
}
