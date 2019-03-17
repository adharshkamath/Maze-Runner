#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SPEED_BOOST_MOVES 15
#define TROLL_NUMBER 3
#define MAX_WEAPONS 2
#define MAX_SPEEDBOOSTERS 1
#define PHASABLE_BLOCKS 3

using namespace std;

int GameCompletion = 0, WindowID;

char maze[35][56]={  
{"+++++++++++++++++++++++++++++++++++++++++++++++++++++++"},
{"+  #           #           #        #              #  +"},
{"+  #           #           #        #              #  +"},
{"+  #  #######  #  ####  #######  ####  ####  ####  #  +"},
{"+           #     #  #        #        #  #  #     #  +"},
{"+           #     #  #        #        #  #  #     #  +"},
{"+######  #  #######  #######  ####  #  #  #  #######  +"},
{"+     #  #           #        #  #  #  #  #        #  +"},
{"+     #  #           #        #  #  #  #  #        #  +"},
{"+  #  ##########  #  #  #######  ####  #  #######  #  +"},
{"+  #           #  #  #     #        #        #     #  +"},
{"+  #           #  #  #     #        #        #     #  +"},
{"+  ##########  ####  ####  #  ####  #######  #  ####  +"},
{"+        #     #  #     #  #     #        #  #        +"},
{"+        #     #  #     #  #     #        #  #        +"},
{"+  ####  ####  #  ####  #  #######  #  #  #  #########+"},
{"+     #     #  #  #     #     #     #  #  #     #     +"},
{"+     #     #  #  #     #     #     #  #  #     #     +"},
{"+#########  #  #  #  #######  #  ####  #  ####  ####  +"},
{"+        #  #        #     #  #     #  #     #        +"},
{"+        #  #        #     #  #     #  #     #        +"},
{"+  ####  #  #######  ####  #  ####  ####  ##########  +"},
{"+  #     #        #        #     #  #  #           #  +"},
{"+  #     #        #        #     #  #  #           #  +"},
{"+  #  #######  #  ####  #######  #  #  ##########  #  +"},
{"+  #        #  #  #  #  #        #           #  #     +"},
{"+  #        #  #  #  #  #        #           #  #     +"},
{"+  #######  #  #  #  ####  #######  #######  #  ######+"},
{"+  #     #  #  #        #        #  #     #           +"},
{"+  #     #  #  #        #        #  #     #           +"},
{"+  #  ####  ####  ####  #######  ####  #  #######  #  +"},
{"+  #              #        #           #           #  +"},
{"+  #              #        #           #           #  +"},
{"+XX++++++++++++++++++++++++++++++++++++++++++++++++++++"} };  


void display_LOSE()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT);
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT);
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
         glColor3f(0.3f,0.45f,0.45f);
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
PhasableBlock Ph[PHASABLE_BLOCKS];
int trollFrameCount = 0;


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
	            if(maze[ T[k].locationY - 1][ T[k].locationX ] == '@' && Player::Armed == 0)        {   T[k].locationY = T[k].locationY -1;  GameCompletion = -1;  }
                else if(maze[ T[k].locationY + 1][ T[k].locationX ] == '@' && Player::Armed == 0)   {   T[k].locationY = T[k].locationY +1;  GameCompletion = -1;  } 
                else if(maze[ T[k].locationY ][ T[k].locationX + 1] == '@' && Player::Armed == 0)    {   T[k].locationX = T[k].locationX +1;  GameCompletion = -1;  } 
                else if(maze[ T[k].locationY ][ T[k].locationX - 1] == '@' && Player::Armed == 0)    {   T[k].locationX = T[k].locationX -1;  GameCompletion = -1;  }
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
                       If no, then try in y-direction. If both does not satisify, then find for x and y direction in opposite side. 
                       */
			        if(maze[ T[k].locationY ][ T[k].locationX + p]==' ')   T[k].locationX = T[k].locationX + p;   //Check for the most feasible move
			        else if(maze[ T[k].locationY + q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY + q;
			        else if(maze[ T[k].locationY ][ T[k].locationX - p]==' ')   T[k].locationX = T[k].locationX - p;
			        else if(maze[ T[k].locationY - q][ T[k].locationX ]==' ')   T[k].locationY = T[k].locationY - q;
		        }
		        else
                {
                       /* If the troll is near to the player in y-direction, first see if the troll could be moved to that position.
                       If no, then try in x-direction. If both does not satisify, then find for x and y direction in opposite side. 
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
    trollFrameCount++;
    if(trollFrameCount >= 500000)
    trollFrameCount %= 500000;
    if(trollFrameCount == 0)
    troll();
}


void display_maze()
{
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glClear(GL_COLOR_BUFFER_BIT);
    glutFullScreen();
    
    double blockWidth = 2.0 / 61.0 ;   
    double blockHeight = 1.5 / 34.0 ;  
    float beginX = -0.9f;
    float beginY = 0.725f;

    int counter = 0;
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

            else if(maze[i][j] == 'X' && GameCompletion == 0)
            {
                glBegin(GL_QUADS);
                   glColor3f(0.5f, 0.5f, 0.5f); 
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
            
            beginX += blockWidth;
        }
        beginY -= blockHeight;
        beginX = -0.9f;
    }
    counter = 0;
    glFlush();
    specialTroll();
    
}


void specialkey_playing(int key, int xr, int yr)
{
   
    switch(key) 
    {
        case GLUT_KEY_UP: 
        if(maze[ P.locationY - 1 ][ P.locationX ] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY - 2 ][ P.locationX ] == ' ' && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
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
        else if(maze[ P.locationY + 1 ][ P.locationX ] == ' ')
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationY   += 1; 
                maze[ P.locationY ][ P.locationX ] = '@';
            }
        break;
        case GLUT_KEY_LEFT: 
        if(maze[ P.locationY ][ P.locationX  - 1] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY ][ P.locationX  - 2] == ' '  && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
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
        else if(maze[ P.locationY ][ P.locationX -1] == ' ')
            {
                maze[ P.locationY ][ P.locationX ] = ' ';
                P.locationX  -= 1; 
                maze[ P.locationY ][ P.locationX ] = '@';
            }
        break;
        case GLUT_KEY_RIGHT: 
        if(maze[ P.locationY ][ P.locationX  + 1] == ' ' && Player::SpeedBoost == 1 && maze[ P.locationY ][ P.locationX  + 2] == ' '  && Player::SpeedBoostCount <= MAX_SPEED_BOOST_MOVES)
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
               maze[ P.locationY ][ P.locationX + 11] = '#';
               P.locationX += 2;
               maze[ P.locationY ][ P.locationX ] = '@';
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
    glutPostRedisplay();
    glFlush();
}


void display()
{
    if(GameCompletion == 0)
    {
        display_maze();
    }
    else if(GameCompletion == 1)
    {
        glFlush();
        glutPostRedisplay();
        usleep(500000);
        display_WIN();
    }
    else if(GameCompletion == -1)
    {
        glFlush();
        glutPostRedisplay();
        usleep(500000);
        display_LOSE();
    }

}


void specialFunc(int key, int v, int c)
{
    if(GameCompletion == 0)
        specialkey_playing(key,v,c);
}


void processNormalKeys(unsigned char key, int x, int y) 
{
    if (key > 0)
		glutDestroyWindow(WindowID);
}


void KeyboardFunction(unsigned char key, int xr, int yr)
{
    if(GameCompletion != 0)
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
