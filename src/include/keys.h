#ifndef KEYS_H
#define KEYS_H

#include <GL/glut.h>
#include <iostream>

extern int GameCompletion, GameBegin, WindowID;

void processNormalKeysForHome(unsigned char key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void KeyboardFunction(unsigned char key, int xr, int yr);

#endif