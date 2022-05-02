#ifndef TROLL_H
#define TROLL_H

#include <GL/glut.h>
#include <stdlib.h>

class Troll
{
    public:
    int locationX, locationY;
    Troll();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};

#endif