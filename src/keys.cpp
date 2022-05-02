#include "include/keys.h"

void processNormalKeysForHome(unsigned char key, int x, int y)
{
     if(key > 0 && key != 27)
		{
            GameBegin = 1;
            glutPostRedisplay();
            glFlush();
        }
     else if(key == 27)
     {
         glutDestroyWindow(WindowID);
     }
}


void processNormalKeys(unsigned char key, int x, int y)
{
    if (key > 0)
		glutDestroyWindow(WindowID);
}


void KeyboardFunction(unsigned char key, int xr, int yr)
{
    processNormalKeysForHome(key,xr,yr);
    if(GameCompletion != 0 && GameBegin == 1)
      processNormalKeys(key,xr,yr);
}