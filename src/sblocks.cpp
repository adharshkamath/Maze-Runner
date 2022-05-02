#include "include/maze.h"
#include "include/sblocks.h"

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

void PhasableBlock::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
    glBegin(GL_QUADS);
        glColor3f(0.6470588f,0.164706f,0.164706f);
        glVertex2f(beginX + blockWidth , beginY);
        glVertex2f(beginX , beginY);
        glVertex2f(beginX , beginY - blockHeight);
        glVertex2f(beginX + blockWidth , beginY - blockHeight);
    glEnd();
}


FieryBlock::FieryBlock()
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

void FieryBlock::Display(float beginX, float beginY, float blockWidth, float blockHeight, int i)
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


Teleport::Teleport()
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

    }
    maze[locationYF][locationXF] = 'T';
    maze[locationYT][locationXT] = 'T';

}


void Teleport::Display(float beginX, float beginY, float blockWidth, float blockHeight, int i)
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