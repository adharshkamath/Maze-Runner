#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void renderbitmap(float x, float y, void *font, char *string);
void initGL();
void display_LOSE();
void display_WIN();
void display_maze();
void display_Home();
void display();
void animate_maze_static();

#endif
