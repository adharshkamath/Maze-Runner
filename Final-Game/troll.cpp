#include "Troll.h"

Troll::Troll()
{
  srand(time(NULL));
  for(;maze[locationY][locationX] != ' ';)
  {
        locationX = rand()%55;
        locationY = rand()%34;
  }
   maze[locationY][locationX] = '*';
}
static void Troll::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
  {
      glBegin(GL_TRIANGLES);
              glColor3f(0.9f, 0.0f, 0.0f);
                  glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                  glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                  glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
              glEnd();
  }
}
