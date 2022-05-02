#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "include/maze.h"
#include "include/display.h"
#include "include/keys.h"
#include "include/player.h"
#include "include/troll.h"
#include "include/extras.h"
#include "include/sblocks.h"
#include "include/exits.h"

using namespace std;

int GameCompletion = 0, WindowID, GameBegin = 0, trollFrameCount = 0, TeleportLocationFixed = 1, firstKeyPressed = 0;

int grid[HEIGHT][WIDTH];
int mazeX, mazeY;

Player P;
Troll T[TROLL_NUMBER];
Weapon W[MAX_WEAPONS];
SpeedBooster S[MAX_SPEEDBOOSTERS];
FieryBlock Fb[FIERY_BLOCKS];
PhasableBlock Ph[PHASABLE_BLOCKS];
Teleport Tlp[TELEPORTATION_STOPS];
ExtraExits E[EXTRA_EXIT_NUMBER];

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


void specialTroll()
{
    if(GameBegin == 1 && GameCompletion == 0 &&  firstKeyPressed == 1)
    {
      trollFrameCount++;
      if(trollFrameCount == 150)
      {
        trollFrameCount = 0;
        troll(T, P);
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


void specialFunc(int key, int v, int c)
{
    if(GameCompletion == 0 && GameBegin == 1)
        {
            specialkey_playing(key, v, c);
            firstKeyPressed = 1;
        }
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
