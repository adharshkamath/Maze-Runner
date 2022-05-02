#include "include/troll.h"

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

void Troll::Display(float beginX, float beginY, float blockWidth, float blockHeight)
{
    glBegin(GL_TRIANGLES);
            glColor3f(0.9f, 0.0f, 0.0f);
                glVertex2f(beginX + (0.65 / 305.0), beginY - (0.3/34.0));
                glVertex2f(beginX + (1.0/61.0), beginY -blockHeight + (0.05/15.0));
                glVertex2f(beginX + (8.0 / 305.0), beginY - (0.3/34.0));
            glEnd();
}

void troll(Troll T[TROLL_NUMBER], Player P)
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

