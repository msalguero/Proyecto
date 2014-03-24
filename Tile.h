#ifndef TILE_H
#define TILE_H


class Tile
{
    public:
        int x,y;
        int tipo;

        Tile(int x, int y, int tipo);
        virtual ~Tile();
    protected:
    private:
};

#endif // TILE_H
