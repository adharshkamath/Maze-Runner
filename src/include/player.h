#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glut.h>
#include <iostream>

class Player
{
    public:
    int locationX, locationY;
    static int SpeedBoost, Armed, SpeedBoostCount;
    Player();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);

};

#endif