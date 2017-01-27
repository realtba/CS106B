#include "cell.h"

DIRECTIONS operator++(DIRECTIONS & dir, int) {
    DIRECTIONS old = dir;
    dir = DIRECTIONS(dir + 1);
return old;
}


Cell::Cell()
{
    this->col=this->row=0;
}

Cell::Cell(int row, int col){
    this->row = row;
    this->col = col;
}
Cell Cell::GetNeighbour(DIRECTIONS dir){
    switch (dir) {
        case NORTH:
            return Cell(this->row-1, this->col);
        case NORTHWEST:
            return Cell(this->row-1, this->col-1 );
        case WEST:
            return Cell(this->row, this->col-1);
        case SOUTHWEST:
            return Cell(this->row+1, this->col-1);
        case SOUTH:
            return Cell(this->row+1, this->col);
        case SOUTHEAST:
            return Cell(this->row+1, this->col+1);
        case EAST:
            return Cell(this->row, this->col+1);
        case NORTHEAST:
            return Cell( this->row-1, this->col+1);
    }
    return *this;
}
