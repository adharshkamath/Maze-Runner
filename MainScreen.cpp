#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <cwchar>




using namespace std;

//INIT function
void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GLUT_SINGLE | GLUT_RGB);
  glLoadIdentity();
  glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, 1.0);
}
void renderbitmap(float x, float y, void *font, char *string){
  char *c;
  glRasterPos2f(x,y);
  for(c=string; *c !='\0';c++){
    glutBitmapCharacter(font,*c);
  }
}

void introscreen(){
  glColor3f(1.f,1.f,1.f);
  //char buf[300]={0};
  char buf1[]="Hello! Welcome to Maze Runner!.Instructions: Use the arrow keys to move the player!";
  renderbitmap(-80,40,GLUT_BITMAP_TIMES_ROMAN_24,buf1);
  char buf2[]={"Press Enter to start the game!. All the best!"};
  renderbitmap(-80,35,GLUT_BITMAP_TIMES_ROMAN_24,buf2);
}
//display function
void display()
{
  introscreen();
  glFlush();
    glutPostRedisplay();
  }

void specialkey(unsigned char key, int x, int y) {

  //this part is a bit messy. the others need to contribute here. It's the enter key handler function.

    switch(key) {
        case 32:
            //Insert CODE FOR STARTING THE GAME
            glutIdleFunc(display);
            //printf("up %f %f\n", xr, yr);
            break;
        default:
            break;
    }
    //glutPostRedisplay();
    //glFlush();
}



int width = 1024;
int height = 768;

int main(int arg, char** argv) {
   glutInit(&arg, argv);          // Initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(width,height);   // Set the window's initial width & height
   glutInitWindowPosition(30, 30); // Position the window's initial top-left corner
   glutCreateWindow("Welcome to Maze Runner!");  // Create window with the given title
   init();
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   //initGL();
   glutKeyboardFunc(specialkey);         // Our own OpenGL initialization
   glutMainLoop();                 // Enter the event-processing loop
   return 0;
}
