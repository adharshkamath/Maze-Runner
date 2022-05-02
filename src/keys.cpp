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
