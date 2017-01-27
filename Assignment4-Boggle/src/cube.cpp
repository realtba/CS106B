#include "cube.h"

Cube::Cube()
{

}
Cube::Cube(string letters)
{
    this->letters = letters;
    this->letterUp =letters.substr(0,1);
    this->isChecked = false;
}

void Cube::rollCube(){
    this->letterUp = letters.at(randomInteger(0,5));
}

char Cube::getLetterUp(){
    return this->letterUp[0];
}

bool Cube::getChecked(){ return this->isChecked;}

void Cube::setChecked(bool check){ this->isChecked = check;}
