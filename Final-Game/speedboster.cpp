#include "SpeedBooster.h"

SpeedBooster::SpeedBooster()
{
  srand(time(NULL));
  for(; maze[locationY][locationX] != ' ';)
  {
        locationX = rand()%55;
        locationY = rand()%34;
  }
    maze[locationY][locationX] = 's';
}
static void SpeedBooster::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
  {
      glBegin(GL_QUADS);
       glColor3f(0.5f,0.0f,0.5f);
       glVertex2f(beginX + (8.0 / 305.0), beginY - (1.5 / 306.0));
       glVertex2f(beginX + (2.0 / 305.0), beginY - (1.5 / 306.0));
       glVertex2f(beginX + (2.0 / 305.0), beginY - (12.0 / 306.0));
       glVertex2f(beginX + (8.0 / 305.0), beginY - (12.0/ 306.0));
      glEnd();
  }
}
