#include "Padre.h"

Padre::Padre()
{
    coordX = 0;
    coordY = 0;
    imagen = NULL;
}

Padre::~Padre()
{
    //dtor
}

vector<Tile*> Padre::getTiles(int xIn,int yIn,int xFin,int yFin, vector<Tile*> tiles)
{
    vector<Tile*> tiles2;
    for (int y = yIn; y <= yIn; y++)
    {
        for (int x = xIn; x <= xFin; x++)
            {
                 for(int i = 0; i<tiles.size(); i++)
                 {
                    if(x == tiles[i]->x && y == tiles[i]->y)
                        tiles2.push_back(new Tile(tiles[i]->x, tiles[i]->y, tiles[i]->tipo));
                 }
            }
    }
    return tiles2;
}

bool Padre::enPantalla(int xObjeto, int yObjeto, int x1, int y1)
{
    if(x1<=xObjeto+50 && (x1+WIDTH_SCREEN)>xObjeto && yObjeto > y1 && yObjeto < (y1+HEIGHT_SCREEN))
        return true;
    return false;
}

bool Padre::puntoEstaDentroDeCaja(int p_x,int p_y,int c_x,int c_y,int c_h,int c_w)
{
    if(p_x>c_x && p_x<c_x+c_w && p_y>c_y && p_y<c_y+c_h)
        return true;
    return false;
}

bool Padre::colisionBasica(int personaje_x,int personaje_y,int enemigo_x,int enemigo_y, int width, int height)
{

    int punto_d_x = personaje_x+40;
    int punto_a_y = personaje_y+40;
    int punto_i_x = personaje_x;
    int punto_ar_y = personaje_y;

    if(puntoEstaDentroDeCaja(punto_d_x, punto_a_y, enemigo_x, enemigo_y, height, width))
        return true;
    if(puntoEstaDentroDeCaja(punto_d_x, punto_ar_y, enemigo_x, enemigo_y, height, width))
        return true;
    if(puntoEstaDentroDeCaja(punto_i_x, punto_a_y, enemigo_x, enemigo_y, height, width))
        return true;
    if(puntoEstaDentroDeCaja(punto_i_x, punto_ar_y, enemigo_x, enemigo_y, height, width))
        return true;
    return false;
}
