#include "Menu.h"

Menu::Menu(SDL_Surface* sc)
{
    seleccion = 1;
    background = IMG_Load("background.png");
    botones = IMG_Load("menu.png");
    instrucciones = IMG_Load("instrucciones.png");
    font = TTF_OpenFont("Frijole-Regular.ttf", 32);
    screen = sc;
    creador = new CreaMapas(screen);
    terminar = false;
    instr = false;
    score = false;
    int cont = 0;
    for(int j = 0; j<2; j++)
    for(int i = 0; i<4 ; i++)
    {
        clips[cont].x = (j * 202);
        clips[cont].y = (i * 52);
        clips[cont].h = 52;
        clips[cont++].w = 202;
    }
    leerScore();
}

Menu::~Menu()
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(botones);
    SDL_FreeSurface(instrucciones);
    TTF_CloseFont(font);
}

void Menu::eventos(SDL_Event* evento)
{
    switch(evento->type)
    {
    case SDL_KEYDOWN :
        switch(evento->key.keysym.sym)
        {
        case SDLK_UP :
            if(seleccion>1 && !instr && !score)
                seleccion--;
            break;
        case SDLK_DOWN :
            if(seleccion<4 && !instr && !score)
                seleccion++;
            break;
        case SDLK_RETURN :
            if(seleccion == 1)
                terminar = true;
            else if(seleccion == 2)
                instr = !instr;
            else if(seleccion == 3)
                score = !score;
            else if(seleccion == 4)
            {
                creador->loop();
            }
            break;
        default :;
        }
        break;
    case SDL_QUIT :
        terminar = true;
        break;
    }
}

void Menu::render()
{
    if(score)
    {
        applySurface(0,0,background);
        SDL_Color textColor = { 0, 0, 0 };
        for(int i = 0; i<3; i++)
        {
            SDL_Surface* mensaje = TTF_RenderText_Solid(font, names[i].c_str(), textColor);
            applySurface(200, 200+(i*50), mensaje);
            SDL_FreeSurface(mensaje);
        }
        for(int i = 0; i<3; i++)
        {
            char c[10];
            sprintf(c, "%d", scores[i]);
            SDL_Surface* mensaje = TTF_RenderText_Solid(font, c, textColor);
            applySurface(400, 200+(i*50), mensaje);
            SDL_FreeSurface(mensaje);
        }
    }else if(instr)
    {
        applySurface(0,0,instrucciones);
    }else
    {
        applySurface(0,0,background);

       if(seleccion == 1)
            applySurface(200, 178, botones, &clips[4]);
        else
            applySurface(200, 178, botones, &clips[0]);
        if(seleccion == 2)
            applySurface(200, 250, botones, &clips[5]);
        else
            applySurface(200, 250, botones, &clips[1]);
        if(seleccion == 3)
            applySurface(200, 322, botones, &clips[6]);
        else
            applySurface(200, 322, botones, &clips[2]);
        if(seleccion == 4)
            applySurface(200, 394, botones, &clips[7]);
        else
            applySurface(200, 394, botones, &clips[3]);
   }
   SDL_Flip(screen);
}

void Menu::applySurface(int x, int y, SDL_Surface* imagen, SDL_Rect* clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(imagen, clip, screen, &offset);
}

void Menu::leerScore()
{
    ifstream in("Scores.txt");
    if(in == NULL)
        return;
    int cont = 0;
    while(in>>names[cont] && in>>scores[cont])
    {
        cont++;
    }
    in.close();
}
