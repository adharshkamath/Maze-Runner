#ifndef EXTRAS_H
#define EXTRAS_H

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

class SpeedBooster
{
    public:
    int locationX, locationY;
    SpeedBooster();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};

class Weapon
{
    public:
    int locationX, locationY;
    Weapon();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};

#endif