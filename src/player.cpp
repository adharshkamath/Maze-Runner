#include "include/maze.h"
#include "include/player.h"

Player::Player()
    {
        generate_maze();
        srand(time(NULL));
        for(; maze[locationY][locationX] != ' ';)
        {
            locationX = rand()%55;
            locationY = rand()%34;
        }
          maze[locationY][locationX] = '@';
    }

void Player::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
    if(Player::SpeedBoost == 0 && Player::Armed == 0 )
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

    else if(Player::SpeedBoost == 0 && Player::Armed == 1)
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

    else if(Player::SpeedBoost == 1 && Player::Armed == 0)
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

int Player::SpeedBoost = 0;
int Player::Armed = 0;
int Player::SpeedBoostCount = 0;
