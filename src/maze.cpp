#include <stdlib.h>
#include "include/maze.h"

int DX[9];
int DY[9];
int OPPOSITE[9];

void clearWallInX(int locationX, int locationY)
{
    maze[locationY][locationX + 2] = ' ';
    maze[locationY + 1][locationX + 2] = ' ';
}


void clearWallInY(int locationX, int locationY)
{
    maze[locationY + 2][locationX] = ' ';
    maze[locationY + 2][locationX + 1] = ' ';
}

int shuffle_array(int *array, int size)
{
  int i;
  for( i = 0; i < (size - 1); i++)
  {
    int r = i + (rand() % (size - i));
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
  return 0;
}

int carve_passage(int cx, int cy, int grid[HEIGHT][WIDTH])
{
    int dx, dy, i;
    int directions[4] = {n, e, s, w};
    shuffle_array(directions, 4);
    for(i = 0; i < 4; i++)
    {
     dx = DX[directions[i]];
     dy = DY[directions[i]];
     if ( ((cx + dx < WIDTH) & (cx + dx >= 0)) & ((cy + dy < HEIGHT) & (cy + dy >= 0)) )
     {
       if (grid[cy + dy][cx + dx] == 0)
       {
         grid[cy][cx] = (grid[cy][cx] | directions[i]);
         grid[cy + dy][cx + dx] = (grid[cy + dy][cx + dx] | OPPOSITE[directions[i]]);
         carve_passage(cx + dx, cy + dy, grid);
       }
     }
    }
    return 0;
}
