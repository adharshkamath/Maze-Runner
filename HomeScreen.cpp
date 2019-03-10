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
//  glClearColor(0.0, 0.0, 0.0, 0.0);
  //glMatrixMode(GLUT_SINGLE | GLUT_RGB);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, 1.0);
}
void renderbitmap(float x, float y, void *font, char *string){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  char *c;
  glRasterPos2f(x,y);
  for(c=string; *c !='\0';c++){
    glutBitmapCharacter(font,*c);
  }
}

void introscreen(){
//  glColor3f(1.f,1.f,1.f);
  //glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  char buf1[]="Hello! Welcome to Maze Runner!.";
  renderbitmap(-80,40,GLUT_BITMAP_HELVETICA_18,buf1);
  char buf2[]="Instructions: Use the arrow keys to move the player!";
  renderbitmap(-80,30,GLUT_BITMAP_HELVETICA_18,buf2);
  char buf3[]="Press Enter to start the game!. All the best!";
  renderbitmap(-80,20,GLUT_BITMAP_HELVETICA_18,buf3);

}
//display function
void display()
{   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  introscreen();
  glFlush();
  //  glutPostRedisplay();
}
//setting up intro introscreen

void specialkey(unsigned char key, int x, int y) {

  //this part is a bit messy. the others need to contribute here. It's the enter key handler function.

    switch(key) {
        case 10:
            //Insert CODE FOR STARTING THE GAME
            glutIdleFunc(display);
            glFlush();
            //printf("up %f %f\n", xr, yr);
            break;
        default:
            glFlush();
            break;
    }
    //glutPostRedisplay();
    //glFlush();
}
//Now we make renderbitmap

int width = 1024;
int height = 768;


int main(int arg, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(50, 50);
   glutCreateWindow("Welcome to Maze Runner!");  // Create window with the given title
   init();
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   //initGL();                       // Our own OpenGL initialization
   //initGL();
   glutIdleFunc(display); // on screen idle
   glutKeyboardFunc(specialkey);         // Our own OpenGL initialization
   glutMainLoop();                 // Enter the event-processing loop
   return 0;
}
