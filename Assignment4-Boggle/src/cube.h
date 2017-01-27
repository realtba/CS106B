#ifndef CUBE_H
#define CUBE_H

#include <string>
#include "random.h"
using namespace std;



class Cube
{
public:
    Cube();
    Cube(string letters);

    void rollCube();
    char getLetterUp();
    void setChecked(bool check);
    bool getChecked();
private:
    string letters;
    string letterUp;
    bool isChecked;
};

#endif // CUBE_H
