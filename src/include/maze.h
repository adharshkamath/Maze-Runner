
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_SPEED_BOOST_MOVES 15
#define TROLL_NUMBER 4
#define MAX_WEAPONS 2
#define MAX_SPEEDBOOSTERS 1
#define PHASABLE_BLOCKS 3
#define FIERY_BLOCKS 3
#define TELEPORTATION_STOPS 2
#define EXTRA_EXIT_NUMBER 1
#define WIDTH 18
#define HEIGHT 11
#define WEIGHT_H 56
#define HEIGHT_H 35

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <utility>

using namespace std;

extern char maze[HEIGHT_H][WEIGHT_H];
extern int grid[HEIGHT][WIDTH];
enum {n = 1, s = 2, e = 4, w = 8};
extern int DX[9];
extern int DY[9];
extern int OPPOSITE[9];
extern vector<pair<int, int>> path;

void clearWallInX(int locationX, int locationY);
void clearWallInY(int locationX, int locationY);
int shuffle_array(int *array, int size);
int carve_passage(int cx, int cy, int grid[HEIGHT][WIDTH]);
int generate_maze();

#endif
