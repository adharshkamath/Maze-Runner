#include "FieryBlock.h"

FieryBlock::FieryBlock()
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
static void FieryBlock::Display(float beginX, float beginY, float blockWidth, float blockHeight, int i)
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
