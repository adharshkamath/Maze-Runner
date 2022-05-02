#ifndef TROLL_H
#define TROLL_H

#include <GL/glut.h>
#include <stdlib.h>
#include "maze.h"
#include "player.h"

extern int GameCompletion;

class Troll
{
    public:
    int locationX, locationY;
    Troll();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};


void troll(Troll T[TROLL_NUMBER], Player P);

#endif