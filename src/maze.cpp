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

int generate_maze()
{
    OPPOSITE[n] = s;
    OPPOSITE[e] = w;
    OPPOSITE[s] = n;
    OPPOSITE[w] = e;

    DX[n] = 0;
    DX[e] = 1;
    DX[s] = 0;
    DX[w] = -1;

    DY[n] = -1;
    DY[e] = 0;
    DY[s] = 1;
    DY[w] = 0;

    int x, y;
    memset(&grid[0], 0, sizeof(grid));
    srand(time(NULL));
    x = rand() % 18;
    y = rand() % 11;
    carve_passage(x, y, grid);
    for(int m = 0; m < 11; m++)
    {
        for(int n = 0; n < 18; n++)
        {
            if((grid[m][n] & 2) != 0)
            {
                clearWallInY((3 * n) + 1, (3 * m) + 1);
            }
            if((grid[m][n] & 4) != 0)
            {
                clearWallInX((3 * n) + 1, (3 * m) + 1);
            }
        }
    }
    return 0;

}