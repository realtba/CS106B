#ifndef CELL_H
#define CELL_H

enum DIRECTIONS {NORTH, NORTHWEST, WEST, SOUTHWEST, SOUTH, SOUTHEAST, EAST, NORTHEAST};
DIRECTIONS operator++(DIRECTIONS & dir, int);
class Cell
{
public:
    Cell();
    Cell(int row, int col);
    Cell GetNeighbour(DIRECTIONS dir);
    int row;
    int col;
};

#endif

