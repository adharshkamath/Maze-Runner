#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

using namespace std;

int GameCompletion = 0, WindowID, GameBegin = 0;

int grid[HEIGHT][WIDTH];
enum {n = 1,e = 4,s = 2,w = 8};
int DX[9];
int DY[9];
int OPPOSITE[9];
int mazeX, mazeY;


char maze[35][56]=
{{"+++++++++++++++++++++++++++++++++++++++++++++++++++++++"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+#####################################################+"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  +"},
 {"+++++++++++++++++++++++++++++++++++++++++++++++++++++++"} };


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


int GenerateMaze()
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


void display_LOSE()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(0.125f, -0.25f);
      glVertex2f(0.375f, -0.25f);
      glVertex2f(0.375f, 0.0f);
      glVertex2f(0.125f, 0.0f);
      glVertex2f(0.125f, 0.25f);
      glVertex2f(0.375f, 0.25f);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(0.875f, -0.25f);
      glVertex2f(0.625f, -0.25f);
      glVertex2f(0.625f, 0.25f);
      glVertex2f(0.875f, 0.25f);

   glEnd();

   glBegin(GL_LINES);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(0.875f, 0.0f);
      glVertex2f(0.625f, 0.0f);
   glEnd();

   glBegin(GL_LINE_LOOP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(-0.125f, -0.25f);
      glVertex2f(-0.375f, -0.25f);
      glVertex2f(-0.375f, 0.25f);
      glVertex2f(-0.125f, 0.25f);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(-0.625f, -0.25f);
      glVertex2f(-0.875f, -0.25f);
      glVertex2f(-0.875f, 0.25f);
   glEnd();

   glFlush();
}


void display_WIN()
{
    glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(0.15f, -0.25f);
      glVertex2f(0.15f, 0.25f);
   glEnd();

   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(0.4f, -0.25f);
      glVertex2f(0.4f, 0.25f);
      glVertex2f(0.7f, -0.25f);
      glVertex2f(0.7f, 0.25f);

   glEnd();

   glBegin(GL_LINE_STRIP);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(-0.1f, 0.25f);
      glVertex2f(-0.25f, -0.25f);
      glVertex2f(-0.4f, 0.25f);
      glVertex2f(-0.55f, -0.25f);
      glVertex2f(-0.7f, 0.25f);
   glEnd();

   glFlush();
}


void initGL()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


class Player
{
    public:
    int locationX, locationY;
    static int SpeedBoost, Armed, SpeedBoostCount;

    Player()
    {
        GenerateMaze();
        srand(time(NULL));
        for(; maze[locationY][locationX] != ' ';)
        {
              locationX = rand()%55;
              locationY = rand()%34;
        }
          maze[locationY][locationX] = '@';
    }

    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        if(SpeedBoost == 0 && Armed == 0 )
            {
                glBegin(GL_TRIANGLES);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex2f(beginX + (1.0/61.0), beginY - (0.05/15.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();
            }

        else if(SpeedBoost == 0 && Armed == 1)
            {
                glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(beginX + (1.0/61.0), beginY - (0.05/15.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();
            }

        else if(SpeedBoost == 1 && Armed == 0)
            {
                glBegin(GL_TRIANGLES);
                glColor3f(0.5f, 0.0f, 0.5f);
                glVertex2f(beginX + (1.0/61.0), beginY - (0.05/15.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY -blockHeight + (0.3/34.0));
                glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();
            }
    }

};


int Player::SpeedBoost = 0;
int Player::Armed = 0;
int Player::SpeedBoostCount = 0;


class Troll
{
    public:
    int locationX, locationY;

    Troll()
    {
        srand(time(NULL));
        for(;maze[locationY][locationX] != ' ';)
        {
              locationX = rand()%55;
              locationY = rand()%34;
        }
         maze[locationY][locationX] = '*';
    }

    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        glBegin(GL_TRIANGLES);
                glColor3f(0.9f, 0.0f, 0.0f);
                    glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                    glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                    glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
                glEnd();
    }

};


class SpeedBooster
{
    public:
    int locationX, locationY;
    SpeedBooster()
    {
        srand(time(NULL));
        for(; maze[locationY][locationX] != ' ';)
        {
              locationX = rand()%55;
              locationY = rand()%34;
        }
          maze[locationY][locationX] = 's';
    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        glBegin(GL_QUADS);
         glColor3f(0.5f,0.0f,0.5f);
         glVertex2f(beginX + (8.0 / 305.0), beginY - (1.5 / 306.0));
         glVertex2f(beginX + (2.0 / 305.0), beginY - (1.5 / 306.0));
         glVertex2f(beginX + (2.0 / 305.0), beginY - (12.0 / 306.0));
         glVertex2f(beginX + (8.0 / 305.0), beginY - (12.0/ 306.0));
        glEnd();
    }
};


class Weapon
{
    public:
    int locationX, locationY;
    Weapon()
    {
        srand(time(NULL));
        for(; maze[locationY][locationX] != ' ';)
        {
              locationX = rand()%55;
              locationY = rand()%34;
        }
          maze[locationY][locationX] = '&';
    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        glBegin(GL_QUADS);
         glColor3f(1.0f,1.0f,0.0f);
         glVertex2f(beginX + (8.0 / 305.0), beginY - (1.5 / 306.0));
         glVertex2f(beginX + (2.0 / 305.0), beginY - (1.5 / 306.0));
         glVertex2f(beginX + (2.0 / 305.0), beginY - (12.0 / 306.0));
         glVertex2f(beginX + (8.0 / 305.0), beginY - (12.0/ 306.0));
        glEnd();
    }

};


class PhasableBlock
{
    public:
    int locationX, locationY;
    PhasableBlock()
    {
        srand(time(NULL));
        while(1)
        {
                  locationX = rand()%55;
                  locationY = rand()%34;
                  if( maze[locationY][locationX] == '#' && ((maze[locationY][locationX - 1] == '#' && maze[locationY][locationX + 1] == '#' && maze[locationY - 1][locationX] == ' ' && maze[locationY + 1][locationX] == ' ') || (maze[locationY - 1][locationX] == '#' && maze[locationY + 1][locationX] == '#' && maze[locationY][locationX - 1] == ' ' && maze[locationY][locationX + 1] == ' ')))
                  break;
                  else
                  continue;

        }
          maze[locationY][locationX] = '!';

    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        glBegin(GL_QUADS);
         glColor3f(0.6470588f,0.164706f,0.164706f);
         glVertex2f(beginX + blockWidth , beginY);
         glVertex2f(beginX , beginY);
         glVertex2f(beginX , beginY - blockHeight);
         glVertex2f(beginX + blockWidth , beginY - blockHeight);
        glEnd();
    }
};


class FieryBlock
{
    public:
    int locationX, locationY;
    FieryBlock()
    {
        srand(time(NULL));
        while(1)
        {
                  locationX = rand()%55;
                  locationY = rand()%34;
                  if( maze[locationY][locationX] == '#' && ((maze[locationY][locationX - 1] == '#' && maze[locationY][locationX + 1] == '#' && maze[locationY - 1][locationX] == ' ' && maze[locationY + 1][locationX] == ' ') || (maze[locationY - 1][locationX] == '#' && maze[locationY + 1][locationX] == '#' && maze[locationY][locationX - 1] == ' ' && maze[locationY][locationX + 1] == ' ')))
                  if( maze[locationY - 1][locationX] != '@' && maze[locationY + 1][locationX] != '@' && maze[locationY][locationX + 1] != '@' && maze[locationY][locationX - 1] != '@')
                  if( maze[locationY - 2][locationX] != '@' && maze[locationY + 2][locationX] != '@' && maze[locationY][locationX + 2] != '@' && maze[locationY][locationX - 2] != '@')
                  if( maze[locationY - 1][locationX - 1] != '@' && maze[locationY + 1][locationX + 1] != '@' && maze[locationY - 1][locationX + 1] != '@' && maze[locationY + 1][locationX - 1] != '@')
                  break;
                  else
                  continue;

        }
          maze[locationY][locationX] = 'F';
          if(maze[locationY][locationX - 1] == '#')
          maze[locationY][locationX - 1] = 'F';
          else if(maze[locationY][locationX + 1] == '#')
          maze[locationY][locationX + 1] = 'F';
          else if(maze[locationY - 1][locationX] == '#')
          maze[locationY - 1][locationX] = 'F';
          else if(maze[locationY + 1][locationX] == '#')
          maze[locationY + 1][locationX] = 'F';
    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight, int i)
    {
        static int BlinkArray[2 * FIERY_BLOCKS] = {0};
        (BlinkArray[i])++;
        if(BlinkArray[i] == 3)
        {
            glBegin(GL_QUADS);
                glColor3f(0.9882f, 0.4f, 0.0f);
                glVertex2f(beginX + blockWidth , beginY);
                glVertex2f(beginX , beginY);
                glVertex2f(beginX , beginY - blockHeight);
                glVertex2f(beginX + blockWidth , beginY - blockHeight);
            glEnd();
                BlinkArray[i] = 0;
        }
        else if(BlinkArray[i] == 2)
        {
            glBegin(GL_QUADS);
                glColor3f(0.97647f, 0.50588f, 0.1647f);
                glVertex2f(beginX + blockWidth , beginY);
                glVertex2f(beginX , beginY);
                glVertex2f(beginX , beginY - blockHeight);
                glVertex2f(beginX + blockWidth , beginY - blockHeight);
            glEnd();
        }
        else 
        {
            glBegin(GL_QUADS);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(beginX + blockWidth , beginY);
                glVertex2f(beginX , beginY);
                glVertex2f(beginX , beginY - blockHeight);
                glVertex2f(beginX + blockWidth , beginY - blockHeight);
            glEnd();
        }

    }

};


class Teleport
{
    public:
    int locationXF, locationYF, locationXT, locationYT;
    Teleport()
    {
        srand(time(NULL));
        while(1)
        {
                  locationXF = rand()%55;
                  locationXT = rand()%55;
                  locationYF = rand()%34;
                  locationYT = rand()%34;
                  if( maze[locationYF][locationXF] == ' ' && maze[locationYT][locationXT] == ' ' && locationYF != locationYT && locationXF != locationXT)
                  if( maze[locationYF - 1][locationXF] != 'F' && maze[locationYF + 1][locationXF] != 'F' && maze[locationYF][locationXF + 1] != 'F' && maze[locationYF][locationXF - 1] != 'F')
                  if( maze[locationYF - 2][locationXF] != 'F' && maze[locationYF + 2][locationXF] != 'F' && maze[locationYF][locationXF + 2] != 'F' && maze[locationYF][locationXF - 2] != 'F')
                  if( maze[locationYT - 1][locationXT] != 'F' && maze[locationYT + 1][locationXT] != 'F' && maze[locationYT][locationXT + 1] != 'F' && maze[locationYT][locationXT - 1] != 'F')
                  if( maze[locationYT - 2][locationXT] != 'F' && maze[locationYT + 2][locationXT] != 'F' && maze[locationYT][locationXT + 2] != 'F' && maze[locationYT][locationXT - 2] != 'F')
                  if( maze[locationYF - 1][locationXF - 1] != 'F' && maze[locationYF + 1][locationXF + 1] != 'F' && maze[locationYF - 1][locationXF + 1] != 'F' && maze[locationYF + 1][locationXF - 1] != 'F')
                  if( maze[locationYT - 1][locationXT - 1] != 'F' && maze[locationYT + 1][locationXT + 1] != 'F' && maze[locationYT - 1][locationXT + 1] != 'F' && maze[locationYT + 1][locationXT - 1] != 'F')
                  break;
                  else
                  continue;

        }
          maze[locationYF][locationXF] = 'T';
          maze[locationYT][locationXT] = 'T';

    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight, int i)
    {

        static int BlinkArray[2 * TELEPORTATION_STOPS] = {0};
        (BlinkArray[i])++;
        if(BlinkArray[i] == 10)
        {
            glBegin(GL_QUADS);
                glColor3f(0.9333f, 0.8666f, 0.509804f);
                glVertex2f(beginX + blockWidth - 1.5 * 0.007f , beginY - 1.5 * 0.007f);
                glVertex2f(beginX + 1.5 * 0.007f , beginY - 1.5 * 0.007f);
                glVertex2f(beginX + 1.5 * 0.007f , beginY - blockHeight + 1.5 * 0.007f);
                glVertex2f(beginX + blockWidth - 1.5 * 0.007f , beginY - blockHeight + 1.5 * 0.007f);
            glEnd();
                BlinkArray[i] = 0;
        }
        else if(BlinkArray[i] % 3 == 0)
        {
            glBegin(GL_QUADS);
                glColor3f(0.98039f, 0.98039f, 0.823529f);
                glVertex2f(beginX + blockWidth - 0.007f/2 , beginY - 0.007f/2 );
                glVertex2f(beginX + 0.007f/2 , beginY - 0.007f/2 );
                glVertex2f(beginX + 0.007f/2 , beginY - blockHeight + 0.007f/2 );
                glVertex2f(beginX + blockWidth - 0.007f/2 , beginY - blockHeight + 0.007f/2 );
            glEnd();
        }
        else 
        {
            glBegin(GL_QUADS);
                glColor3f(0.854902f, 0.647058f, 0.125490f);
                glVertex2f(beginX + blockWidth - 0.007f/3 , beginY - 0.007f/3);
                glVertex2f(beginX + 0.007f/3 , beginY - 0.007f/3);
                glVertex2f(beginX + 0.007f/3 , beginY - blockHeight + 0.007f/3);
                glVertex2f(beginX + blockWidth - 0.007f/3 , beginY - blockHeight + 0.007f/3);
            glEnd();
        }

    }

};


class ExtraExits
{
    public:
    int locationX, locationY;
    ExtraExits()
    {
        srand(time(NULL));
        while(1)
        {
            locationX = rand()%55;
            locationY = rand()%34;
            if( maze[locationY][locationX] == '+' )
            {
                if( (locationX == 0 && maze[locationY][locationX + 1] == ' ') || (locationX == 54 && maze[locationY][locationX - 1] == ' ') )
                    break;
                if( (locationY == 0 && maze[locationY + 1][locationX] == ' ') || (locationY == 33 && maze[locationY - 1][locationX] == ' ') )
                    break;
            }
            else
            continue;
        }
          maze[locationY][locationX] = 'X';
          if(maze[locationY][locationX - 1] == '+' && maze[locationY + 1][locationX - 1] == ' ')
          maze[locationY][locationX - 1] = 'X';
          else if(maze[locationY][locationX + 1] == '+' && maze[locationY + 1][locationX + 1] == ' ')
          maze[locationY][locationX + 1] = 'X';
          else if(maze[locationY][locationX - 1] == '+' && maze[locationY - 1][locationX - 1] == ' ')
          maze[locationY][locationX - 1] = 'X';
          else if(maze[locationY][locationX + 1] == '+' && maze[locationY - 1][locationX + 1] == ' ')
          maze[locationY][locationX + 1] = 'X';
          else if(maze[locationY - 1][locationX] == '+' && maze[locationY - 1][locationX + 1] == ' ')
          maze[locationY - 1][locationX] = 'X';
          else if(maze[locationY + 1][locationX] == '+' && maze[locationY + 1][locationX + 1] == ' ')
          maze[locationY + 1][locationX] = 'X';
          else if(maze[locationY - 1][locationX] == '+' && maze[locationY - 1][locationX - 1] == ' ')
          maze[locationY - 1][locationX] = 'X';
          else if(maze[locationY + 1][locationX] == '+' && maze[locationY + 1][locationX - 1] == ' ')
          maze[locationY + 1][locationX] = 'X';
    }
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight)
    {
        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.39218f, 0.0f);
                glVertex2f(beginX + blockWidth , beginY);
                glVertex2f(beginX , beginY);
                glVertex2f(beginX , beginY - blockHeight);
                glVertex2f(beginX + blockWidth , beginY - blockHeight);
        glEnd();
    }

};

Player P;
Troll T[TROLL_NUMBER];
Weapon W[MAX_WEAPONS];
SpeedBooster S[MAX_SPEEDBOOSTERS];
FieryBlock Fb[FIERY_BLOCKS];
PhasableBlock Ph[PHASABLE_BLOCKS];
Teleport Tlp[TELEPORTATION_STOPS];
ExtraExits E[EXTRA_EXIT_NUMBER];

int trollFrameCount = 0, TeleportLocationFixed = 1, firstKeyPressed = 0;

void TeleportPlayer(int locationX, int locationY)
{
    for(int i = 0; i < TELEPORTATION_STOPS; i++)
    {

        if(Tlp[i].locationXF == locationX && Tlp[i].locationYF == locationY)
        {
            maze[locationY][locationX] = 'T';
            P.locationX = Tlp[i].locationXT;
            P.locationY = Tlp[i].locationYT;
            maze[P.locationY][P.locationX] = '@';
            glutPostRedisplay();
            glFlush();
        }
        else if(Tlp[i].locationXT == locationX && Tlp[i].locationYT == locationY)
        {
            maze[locationY][locationX] = 'T';
            P.locationX = Tlp[i].locationXF;
            P.locationY = Tlp[i].locationYF;
            maze[P.locationY][P.locationX] = '@';
            glutPostRedisplay();
            glFlush();
        }
    }

}

void troll()
{
    int i, j, k = 0;
    while(k < TROLL_NUMBER)
    {
        if(maze[T[k].locationY][T[k].locationX] == '*')
	    {
            i = T[k].locationX;
	        j = T[k].locationY;
                                       //Check if the troll is next to the player
	            if(maze[ T[k].locationY - 1][ T[k].locationX ] == '@' && Player::Armed == 0 )        {   T[k].locationY = T[k].locationY -1;  GameCompletion = -1;  }
                else if(maze[ T[k].locationY + 1][ T[k].locationX ] == '@' && Player::Armed == 0 )   {   T[k].locationY = T[k].locationY +1;  GameCompletion = -1;  }
                else if(maze[ T[k].locationY ][ T[k].locationX + 1] == '@' && Player::Armed == 0 )    {   T[k].locationX = T[k].locationX +1;  GameCompletion = -1;  }
                else if(maze[ T[k].locationY ][ T[k].locationX - 1] == '@' && Player::Armed == 0 )    {   T[k].locationX = T[k].locationX -1;  GameCompletion = -1;  }
            {
		        int p = 1,q = 1;
                  //Assign p and q values to in according to the position(left, top, bottom, right) of the troll w.r.t. player
		         if( T[k].locationX > P.locationX )   p = -1;
		         if( T[k].locationY > P.locationY )   q = -1;
                   //Check if the troll and the player are in same line
                if( T[k].locationX == P.locationX )
                {
                    if(maze[ T[k].locationY + q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY + q;
		            else if(maze[ T[k].locationY - q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY - q;
		            else if(maze[ T[k].locationY ][ T[k].locationX + p]==' ')   T[k].locationX = T[k].locationX + p;
		            else if(maze[ T[k].locationY ][ T[k].locationX - p]==' ')   T[k].locationX = T[k].locationX - p;
                }
                else if( T[k].locationY == P.locationY )
                {
                    if(maze[ T[k].locationY ][ T[k].locationX + p]==' ')   T[k].locationX = T[k].locationX + p;
		            else if(maze[ T[k].locationY ][ T[k].locationX - p]==' ')   T[k].locationX = T[k].locationX - p;
		            else if(maze[ T[k].locationY + q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY + q;
		            else if(maze[ T[k].locationY - q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY - q;
                }
                //Check in which direction is the troll near to the player
                else if(abs( T[k].locationX - P.locationX) < abs( T[k].locationY - P.locationY))
                {
                       /* If the troll is near to the player in x-direction, first see if the troll could be moved to that position.
                       If no, then try in y-direction. If both does not satisfy, then find for x and y direction in opposite side.
                       */
			        if(maze[ T[k].locationY ][ T[k].locationX + p]==' ')   T[k].locationX = T[k].locationX + p;   //Check for the most feasible move
			        else if(maze[ T[k].locationY + q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY + q;
			        else if(maze[ T[k].locationY ][ T[k].locationX - p]==' ')   T[k].locationX = T[k].locationX - p;
			        else if(maze[ T[k].locationY - q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY - q;
		        }
		        else
                {
                       /* If the troll is near to the player in y-direction, first see if the troll could be moved to that position.
                       If no, then try in x-direction. If both does not satisfy, then find for x and y direction in opposite side.
                       */
		            if(maze[ T[k].locationY + q][ T[k].locationX ]==' ')  T[k].locationY = T[k].locationY + q;
		            else if(maze[ T[k].locationY ][ T[k].locationX + p]==' ')   T[k].locationX = T[k].locationX + p;
		            else if(maze[ T[k].locationY - q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY - q;
		                 //else if(maze[ T[k].locationY ][ T[k].locationX -p]==' ')   T[k].locationX = T[k].locationX -p;
		        }
	        }
	          maze[j][i] = ' ';
	          maze[ T[k].locationY ][ T[k].locationX ] = '*';
              glutPostRedisplay();
              glFlush();
        }
        k++;
    }
}


void specialTroll()
{
    if(GameBegin == 1 && GameCompletion == 0 &&  firstKeyPressed == 1)
    {
      trollFrameCount++;
      if(trollFrameCount == 150)
      {
        trollFrameCount = 0;
        troll();
      }
    }

}


void FixTeleportlocations()
{
    for(int i = 0; i < TELEPORTATION_STOPS; i++)
    {
        maze[Tlp[i].locationYF][Tlp[i].locationXF] = 'T';
        maze[Tlp[i].locationYT][Tlp[i].locationXT] = 'T';
    }
}


void display_maze()
{

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutFullScreen();

    double blockWidth = 2.0 / 61.0 ;
    double blockHeight = 1.5 / 34.0 ;
    float beginX = -0.9f;
    float beginY = 0.725f;
    int a = 0, b = 0;

    for(int i = 0; i < 34; i++)
    {
        for(int j = 0; j < 55; j++)
        {
            if(maze[i][j] == '#' || maze[i][j] == '+' )
            {
                glBegin(GL_QUADS);
                   glColor3f(1.0f, 1.0f, 1.0f);
                   glVertex2f(beginX + blockWidth , beginY);
                   glVertex2f(beginX , beginY);
                   glVertex2f(beginX , beginY - blockHeight);
                   glVertex2f(beginX + blockWidth , beginY - blockHeight);
                glEnd();
            }

            else if(maze[i][j] == '@')
            {
                P.Display(beginX, beginY, blockWidth, blockHeight);
            }

            else if(maze[i][j] == 'X' )
            {
                glBegin(GL_QUADS);
                   glColor3f(0.0f, 0.39218f, 0.0f);
                   glVertex2f(beginX + blockWidth , beginY);
                   glVertex2f(beginX , beginY);
                   glVertex2f(beginX , beginY - blockHeight);
                   glVertex2f(beginX + blockWidth , beginY - blockHeight);
                glEnd();
            }

            else if(maze[i][j] == '*')
            {
                Troll::Display(beginX, beginY, blockWidth, blockHeight);
            }

            else if(maze[i][j] == '&')
            {
                Weapon::Display(beginX, beginY, blockWidth, blockHeight);
            }

            else if(maze[i][j] == 's')
            {
                SpeedBooster::Display(beginX, beginY, blockWidth, blockHeight);
            }

            else if(maze[i][j] == '!')
            {
                PhasableBlock::Display(beginX, beginY, blockWidth, blockHeight);

            }

            else if(maze[i][j] == 'F')
            {
                FieryBlock::Display(beginX, beginY, blockWidth, blockHeight, a); a++;
            }

            else if(maze[i][j] == 'T')
            {
                Teleport::Display(beginX, beginY, blockWidth, blockHeight, b); b++;
            }


            beginX += blockWidth;
        }
        beginY -= blockHeight;
        beginX = -0.9f;
    }
    glFlush();

}


void specialkey_playing(int key, int xr, int yr)
{
    if(TeleportLocationFixed == 0)
            FixTeleportlocations();
    switch(key)
    {
        case GLUT_KEY_UP:

        if(maze[ P.locationY - 1][ P.locationX ] == 'X')
        {
            maze[ P.locationY ][ P.locationX ] = ' ';
            maze[ --P.locationY  ][ P.locationX ] = '@';
            GameCompletion = 1;
        }
        else if((maze[ P.locationY - 1 ][ P.locationX ] == ' ' ) && (maze[ P.locationY - 2 ][ P.locationX ] == 'F' || maze[ P.locationY - 2 ][ P.locationX - 1 ] == 'F' || maze[ P.locationY - 2 ][ P.locationX + 1] == 'F'))
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                GameCompletion = -1;
            }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY - 2 ][ P.locationX ] == ' ' && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 2;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoostCount++;
            }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == '*' && Player::Armed == 1)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 0;
            }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == '&' && Player::Armed == 0 && Player::SpeedBoost == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 1;
            }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == 's' && Player::SpeedBoost == 0 && Player::Armed == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoost = 1;
            }
        else if(maze[P.locationY - 1][ P.locationX ] == '!' )
           {
               maze[ P.locationY ][ P.locationX ] = ' ';
               maze[ P.locationY - 1][ P.locationX ] = '#';
               P.locationY -= 2;
               maze[ P.locationY ][ P.locationX ] = '@';
           }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == 'T' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                TeleportPlayer(P.locationX, P.locationY);
                TeleportLocationFixed = 0;

            }
        else if(maze[ P.locationY - 1 ][ P.locationX ] == ' ' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
            }

        break;
        case GLUT_KEY_DOWN:

        if(maze[ P.locationY + 1][ P.locationX ] == 'X')
        {
            maze[ P.locationY ][ P.locationX ] = ' ';
            maze[ ++P.locationY  ][ P.locationX ] = '@';
            GameCompletion = 1;
        }
        else if((maze[ P.locationY + 1 ][ P.locationX ] == ' ' ) && (maze[ P.locationY + 2 ][ P.locationX ] == 'F' || maze[ P.locationY + 2 ][ P.locationX - 1] == 'F' || maze[ P.locationY + 2 ][ P.locationX + 1] == 'F'))
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                GameCompletion = -1;
            }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY + 2 ][ P.locationX ] == ' '  && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 2;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoostCount++;
            }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == '*' && Player::Armed == 1)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 0;
            }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == '&' && Player::Armed == 0 && Player::SpeedBoost == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 1;
            }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == 's' && Player::SpeedBoost == 0 && Player::Armed == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoost = 1;
            }
        else if(maze[P.locationY + 1][ P.locationX ] == '!' )
           {
               maze[ P.locationY ][ P.locationX ] = ' ';
               maze[ P.locationY + 1][ P.locationX ] = '#';
               P.locationY += 2;
               maze[ P.locationY ][ P.locationX ] = '@';
           }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == 'T' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                TeleportPlayer(P.locationX, P.locationY);
                TeleportLocationFixed = 0;

            }
        else if(maze[ P.locationY + 1 ][ P.locationX ] == ' ')
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
            }
        break;
        case GLUT_KEY_LEFT:

        if(maze[ P.locationY ][ P.locationX - 1] == 'X')
        {
            maze[ P.locationY ][ P.locationX ] = ' ';
            maze[ P.locationY  ][ --P.locationX ] = '@';
            GameCompletion = 1;
        }
        else if((maze[ P.locationY ][ P.locationX - 1 ] == ' ' ) && (maze[ P.locationY ][ P.locationX - 2 ] == 'F' || maze[ P.locationY - 1][ P.locationX - 2 ] == 'F' || maze[ P.locationY + 1][ P.locationX - 2] == 'F'))
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                GameCompletion = -1;
            }
        else if(maze[ P.locationY ][ P.locationX  - 1] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY ][ P.locationX  - 2] == ' '  && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 2;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoostCount++;
            }
        else if(maze[ P.locationY ][ P.locationX  - 1] == '*' && Player::Armed == 1)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 0;
            }
        else if(maze[ P.locationY ][ P.locationX  - 1] == '&' && Player::Armed == 0 && Player::SpeedBoost == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 1;
            }
        else if(maze[ P.locationY ][ P.locationX  - 1] == 's' && Player::SpeedBoost == 0 && Player::Armed == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoost = 1;
            }
        else if(maze[P.locationY ][ P.locationX - 1] == '!' )
           {
               maze[ P.locationY ][ P.locationX ] = ' ';
               maze[ P.locationY ][ P.locationX - 1 ] = '#';
               P.locationX -= 2;
               maze[ P.locationY ][ P.locationX ] = '@';
           }
        else if(maze[ P.locationY ][ P.locationX - 1] == 'T' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                TeleportPlayer(P.locationX, P.locationY);
                TeleportLocationFixed = 0;

            }
        else if(maze[ P.locationY ][ P.locationX -1] == ' ')
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 1;
                maze[ P.locationY ][ P.locationX ] = '@';
            }
        break;
        case GLUT_KEY_RIGHT:

        if(maze[ P.locationY ][ P.locationX + 1] == 'X')
        {
            maze[ P.locationY ][ P.locationX ] = ' ';
            maze[ P.locationY  ][ ++P.locationX ] = '@';
            GameCompletion = 1;
        }
        else if((maze[ P.locationY ][ P.locationX + 1 ] == ' ' ) && (maze[ P.locationY ][ P.locationX + 2 ] == 'F' || maze[ P.locationY - 1][ P.locationX + 2 ] == 'F' || maze[ P.locationY + 1][ P.locationX + 2] == 'F'))
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                GameCompletion = -1;
            }
        else if(maze[ P.locationY ][ P.locationX  + 1] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY ][ P.locationX  + 2] == ' '  && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  += 2;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoostCount++;
            }
        else if(maze[ P.locationY ][ P.locationX  + 1] == '*' && Player::Armed == 1)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 0;
            }
        else if(maze[ P.locationY ][ P.locationX  + 1] == '&' && Player::Armed == 0 && Player::SpeedBoost == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::Armed = 1;
            }
        else if(maze[ P.locationY ][ P.locationX  + 1] == 's' && Player::SpeedBoost == 0 && Player::Armed == 0)
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                Player::SpeedBoost = 1;
            }
        else if(maze[P.locationY ][ P.locationX + 1] == '!' )
           {
               maze[ P.locationY ][ P.locationX ] = ' ';
               maze[ P.locationY ][ P.locationX + 1] = '#';
               P.locationX += 2;
               maze[ P.locationY ][ P.locationX ] = '@';
           }
        else if(maze[ P.locationY ][ P.locationX + 1] == 'T' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
                TeleportPlayer(P.locationX, P.locationY);
                TeleportLocationFixed = 0;

            }
        else if(maze[ P.locationY ][ P.locationX +1] == ' ' )
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  += 1;
                maze[ P.locationY ][ P.locationX ] = '@';
            }
        break;
    }
    if(Player::SpeedBoostCount > MAX_SPEED_BOOST_MOVES)
    Player::SpeedBoost = 0;
    if(TeleportLocationFixed == 0)
        FixTeleportlocations();
    glutPostRedisplay();
    glFlush();
}


void renderbitmap(float x, float y, void *font, char *string)
{
  char *c;
  glRasterPos2f(x,y);
  for( c = string; *c != '\0'; c++)
    glutBitmapCharacter( font, *c);

}


void display_Home()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutFullScreen();
    double blockWidth = 2.0 / 61.0 ;
    double blockHeight = 1.5 / 34.0 ;
    char buf1[]="Welcome to Maze Runner!";
    renderbitmap(-0.8f,0.85f - 0.05f,GLUT_BITMAP_9_BY_15,buf1);
    char buf2[]="For the sake of the game, you, my friend, are a weird looking green creature still unknown to mankind";
    renderbitmap(-0.8f,0.75f - 0.05f,GLUT_BITMAP_9_BY_15,buf2);
    char buf21[]="Right now, you're stuck in a maze and your task is to get out of it alive";
    renderbitmap(-0.8f,0.65f - 0.05f,GLUT_BITMAP_9_BY_15,buf21);
    char buf212[]="You look something like this -> ";
    renderbitmap(-0.8f,0.55f - 0.05f,GLUT_BITMAP_9_BY_15,buf212);
    Player::Display(-0.5f, 0.58f - 0.05f, blockWidth, blockHeight);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf3[]="Use the arrow keys to move up, down, right or left ";
    renderbitmap(-0.8f,0.45f - 0.05f,GLUT_BITMAP_9_BY_15,buf3);
    char buf4[]="Watch out for the red coloured TROLLS that look like this ->      They are trying to kill you. (don't let them stop you :P)";
    renderbitmap(-0.8f,0.35f - 0.05f,GLUT_BITMAP_9_BY_15,buf4);
    Troll::Display(-0.227f, 0.38f - 0.05f, blockWidth, blockHeight);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf5[]="There will be some WEAPONS, which look like this ->      and SPEED BOOSTERS, which look like this ->     ";
    renderbitmap(-0.8f,0.25f - 0.05f,GLUT_BITMAP_9_BY_15,buf5);
    Weapon::Display(-0.315f,0.282f - 0.05f,blockWidth, blockHeight );
    SpeedBooster::Display(0.15f, 0.282f - 0.05f,blockWidth, blockHeight );
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf51[] = "We put them to help you get out of the maze";
    renderbitmap(-0.8f,0.15f - 0.05f,GLUT_BITMAP_9_BY_15,buf51);
    char buf6[]="The Speedbooster increases the player's speed. You can use a weapon to kill only one troll (don't be too greedy smh) ";
    renderbitmap(-0.8f,0.05f - 0.05f,GLUT_BITMAP_9_BY_15,buf6);
    char buf7[]="At any instant, you can have either a weapon or a speedbooster, but not both";
    renderbitmap(-0.8f,-0.05f - 0.05f,GLUT_BITMAP_9_BY_15,buf7);
    char buf8[]="There are certain blocks in the maze that are brownish like this ->      These are phasable walls which you can pass through only once (like Flash :D)";
    renderbitmap(-0.8f,-0.15f - 0.05f,GLUT_BITMAP_9_BY_15,buf8);
    PhasableBlock::Display(-0.16f, -0.12f - 0.05f, blockWidth, blockHeight);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf81[]="There are certain orangish glowing blocks like this ->      These are fiery walls. You go even near them, and boom! you're dead";
    renderbitmap(-0.8f,-0.25f - 0.05f,GLUT_BITMAP_9_BY_15,buf81);
    FieryBlock::Display(-0.285f, -0.222f - 0.05f, blockWidth, blockHeight,1);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf811[]="Then there are places like this in the maze ->     These are teleporting locations. (The pairing of these locations is random XD)";
    renderbitmap(-0.8f,-0.35f - 0.05f,GLUT_BITMAP_9_BY_15,buf811);
    Teleport::Display(-0.365f, -0.322f - 0.05f, blockWidth, blockHeight,1);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf9[]="The Exits will look like this ->       Press ENTER to start the game";
    renderbitmap(-0.8f,-0.45f - 0.05f,GLUT_BITMAP_9_BY_15,buf9);
    ExtraExits::Display(-0.47f - 0.02f, -0.42f - 0.05f, blockWidth, blockHeight);
    glColor3f(1.0f, 1.0f, 1.0f);
    char buf10[]="All the best! :\")";
    renderbitmap(-0.8f,-0.55f - 0.05f,GLUT_BITMAP_9_BY_15,buf10);
    char buf11[]="NOTE : Pls dont let us down. Plis. Get out alive.";
    renderbitmap(-0.8f,-0.65f - 0.05f,GLUT_BITMAP_9_BY_15,buf11);
    char buf12[]="(Also.. you can press Esc and quit the game anytime)";
    renderbitmap(-0.8f,-0.75f - 0.05f,GLUT_BITMAP_9_BY_15,buf12);
    glFlush();
    glutPostRedisplay();
}


void display()
{
    if(GameBegin == 0)
    {
        display_Home();
    }
    else if(GameCompletion == 0 && GameBegin == 1)
    {
        glFlush();
        glutPostRedisplay();
        display_maze();
    }
    else if(GameCompletion == 1 && GameBegin == 1)
    {

        usleep(50000);
        display_WIN();
    }
    else if(GameCompletion == -1 && GameBegin == 1)
    {

        usleep(50000);
        display_LOSE();
    }

}


void specialFunc(int key, int v, int c)
{
    if(GameCompletion == 0 && GameBegin == 1)
        {
            specialkey_playing(key,v,c);
            firstKeyPressed = 1;
        }
}


void processNormalKeysForHome(unsigned char key, int x, int y)
{
     if(key > 0 && key != 27)
		{
            GameBegin = 1;
            glutPostRedisplay();
            glFlush();
        }
     else if(key == 27)
     {
         glutDestroyWindow(WindowID);
     }
}


void processNormalKeys(unsigned char key, int x, int y)
{
    if (key > 0)
		glutDestroyWindow(WindowID);
}


void KeyboardFunction(unsigned char key, int xr, int yr)
{
    processNormalKeysForHome(key,xr,yr);
    if(GameCompletion != 0 && GameBegin == 1)
      processNormalKeys(key,xr,yr);
}


int main(int argc, char** argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);

    WindowID = glutCreateWindow("Maze Runner");

    glutDisplayFunc(display);

    glutIdleFunc(specialTroll);

    glutSpecialFunc(specialFunc);

    glutKeyboardFunc(KeyboardFunction);

    initGL();

    glutMainLoop();

    return 0;

}
