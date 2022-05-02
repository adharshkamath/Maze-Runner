#ifndef SBLOCKS_H
#define SBLOCKS_H

#include <GL/glut.h>
#include <stdlib.h>
#include "maze.h"
#include "player.h"

class PhasableBlock
{
    public:
    int locationX, locationY;
    PhasableBlock();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);
};


class FieryBlock
{
    public:
    int locationX, locationY;
    FieryBlock();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight, int i);
};


class Teleport
{
    public:
    int locationXF, locationYF, locationXT, locationYT;
    Teleport();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight, int i);
};

#endif