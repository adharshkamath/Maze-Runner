#include "PhasableBlock.h"

PhasableBlock::PhasableBlock()
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
static void PhasableBlock::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
  glBegin(GL_QUADS);
   glColor3f(0.6470588f,0.164706f,0.164706f);
   glVertex2f(beginX + blockWidth , beginY);
   glVertex2f(beginX , beginY);
   glVertex2f(beginX , beginY - blockHeight);
   glVertex2f(beginX + blockWidth , beginY - blockHeight);
  glEnd();
}
