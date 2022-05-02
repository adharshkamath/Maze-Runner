#include "include/maze.h"
#include "include/exits.h"

ExtraExits::ExtraExits()
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

void ExtraExits::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.39218f, 0.0f);
            glVertex2f(beginX + blockWidth , beginY);
            glVertex2f(beginX , beginY);
            glVertex2f(beginX , beginY - blockHeight);
            glVertex2f(beginX + blockWidth , beginY - blockHeight);
    glEnd();
}
