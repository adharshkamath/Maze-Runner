#ifndef EXITS_H
#define EXITS_H

#include <GL/glut.h>
#include <stdlib.h>

class ExtraExits
{
    public:
    int locationX, locationY;
    ExtraExits();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};

#endif