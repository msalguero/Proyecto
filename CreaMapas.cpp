#include "CreaMapas.h"

CreaMapas::CreaMapas(SDL_Surface* screen)
{
    mouseX = mouseY = 0;
    xMapa = -50;
    yMapa = -50;
    vel = 0;
    click = false;
    seleccion = 1;
    this->screen = screen;
    background = IMG_Load("endless.png");
    source = IMG_Load("Objetos.png");
    tiles = IMG_Load("TilePool.png");
    mouse = IMG_Load("Borrador.png");
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
            if(mapa[i][k] == 4)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 0;
                clip.y = 90;
                clip.w = 90;
                clip.h = 200;
                applySurface(xCoor, yCoor, &clip);
            }
            else
            if(mapa[i][k] == 5)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 4*50;
                clip.y = 0;
                clip.w = clip.h = 50;
                applySurface(xCoor, yCoor, &clip);
            }
            else if(mapa[i][k] == 6)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 5*50;
                clip.y = 0;
                clip.w = 100;
                clip.h = 100;
                applySurface(xCoor, yCoor, &clip);
            }
            else if(mapa[i][k] == 9)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 0;
                clip.y = 50+2;
                clip.w = 100;
                clip.h = 42;
                applySurface(xCoor, yCoor, &clip);
//                tiles.push_back(new Tile(0, 0, 0));
//                plataformas.push_back(new PlataformaMovible(xCoor, yCoor, IMGplataformas[1]));
            }else if(mapa[i][k] == 8)
            {
                int xCoor = k*50;
                int yCoor = i*50;
                SDL_Rect clip;
                clip.x = 126;
                clip.y = 50+2;
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
        renderMouse();
        renderTileChooser();
}

void CreaMapas::applySurface(int x, int y, SDL_Rect* clip)
{
     //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x-xMapa;
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
            eventos(&event);
            switch(event.type)
            {
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_DOWN :
                            if(seleccion<9)
                            {
                                seleccion++;
                                if(seleccion == 7)
                                    seleccion++;
                            }
                            break;
                        case SDLK_UP :
                            if(seleccion>1)
                            {
                                seleccion--;
                                if(seleccion == 7)
                                    seleccion--;
                            }
                            break;
                        default : ;
                    }
                    break;
                case SDL_QUIT :
                    running = false;
            }
        }
        moverCamara();
        render();

        SDL_Flip(screen);
    }
    escribirMapa();
}

void CreaMapas::escribirMapa()
{
ofstream out("MapaUsuario.txt");
    if(out == NULL)
        return;
    for(int h = 0; h<HEIGHT; h++)
    {
        for(int w = 0; w<WIDTH; w++)
        {
            out<<mapa[h][w];
            out<<" ";
        }
        out<<endl;
    }
    out.close();
}

void CreaMapas::eventos(SDL_Event* evento)
{
 switch(evento->type)
    {
    case SDL_KEYDOWN :
        switch(evento->key.keysym.sym)
        {
        case SDLK_b:
            if(seleccion == 0)
                seleccion = 1;
            else
                seleccion = 0;
            break;
        case SDLK_LEFT :
                vel = -4;
            break;
        case SDLK_RIGHT :
                vel = 4;
            break;
        case SDLK_SPACE :

            break;
        case SDLK_RETURN :

            break;
        default :;
        }
        break;

    case SDL_KEYUP :
        switch(evento->key.keysym.sym)
        {
        case SDLK_LEFT :
                vel = 0;
            break;
        case SDLK_RIGHT :
                vel = 0;
            break;
        default :;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        click = true;
        for(int h = 0; h<HEIGHT; h++)
        for(int w = 0; w<WIDTH; w++)
        {
            if(puntoEstaDentroDeCaja(evento->button.x+xMapa, evento->button.y, w*50, h*50, 50, 50) && click)
                mapa[h][w] = seleccion;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        click = false;
        break;

    case SDL_MOUSEMOTION:
        mouseX = evento->button.x;
        mouseY = evento->button.y;
        for(int h = 0; h<HEIGHT; h++)
        for(int w = 0; w<WIDTH; w++)
        {
            if(puntoEstaDentroDeCaja(evento->button.x+xMapa, evento->button.y, w*50, h*50, 50, 50) && click)
                mapa[h][w] = seleccion;
        }
        break;
    default : ;
    }
}

void CreaMapas::moverCamara()
{
    if(camara.x<0)
    {
        vel = 0;
        camara.x+=4;
    }else if(camara.x >= 2688-640)
    {
        vel = 0;
        camara.x-=4;
    }
    camara.x += vel;
    xMapa += vel;
}

bool CreaMapas::puntoEstaDentroDeCaja(int p_x,int p_y,int c_x,int c_y,int c_h,int c_w)
{
    if(p_x>c_x && p_x<c_x+c_w && p_y>c_y && p_y<c_y+c_h)
        return true;
    return false;
}

void CreaMapas::renderTileChooser()
{
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    SDL_Rect clip;
    clip.y = 0;
    clip.w = 50;
    clip.h = 480;
    switch(seleccion)
    {
    case 1:
        clip.x = 0;
        break;
    case 2:
        clip.x = 53;
        break;
    case 3:
        clip.x = 106;
        break;
    case 4:
        clip.x = 159;
        break;
    case 5:
        clip.x = 212;
        break;
    case 6:
        clip.x = 265;
        break;
    case 8:
        clip.x = 318;
        break;
    case 9:
        clip.x = 371;
        break;
    }
    SDL_BlitSurface(tiles, &clip, screen, NULL);
}

void CreaMapas::renderMouse()
{
    SDL_Rect offset;
    offset.x = mouseX;
    offset.y = mouseY;

    SDL_Rect clip;
    clip.x = 20;
    clip.y = 0;
    clip.w = 22;
    clip.h = 20;
    if(seleccion == 0)
    {
        clip.x = 0;
    }

    SDL_BlitSurface(mouse, &clip, screen, &offset);
}
