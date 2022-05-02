#include "include/maze.h"
#include "include/keys.h"
#include "include/display.h"
#include "include/player.h"
#include "include/troll.h"
#include "include/extras.h"
#include "include/sblocks.h"
#include "include/exits.h"

void renderbitmap(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display_LOSE()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
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
	glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
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

void display_maze()
{

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutFullScreen();

	double blockWidth = 2.0 / 61.0;
	double blockHeight = 1.5 / 34.0;
	float beginX = -0.9f;
	float beginY = 0.725f;
	int a = 0, b = 0;

	for (int i = 0; i < 34; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			if (maze[i][j] == '#' || maze[i][j] == '+')
			{
				glBegin(GL_QUADS);
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(beginX + blockWidth, beginY);
				glVertex2f(beginX, beginY);
				glVertex2f(beginX, beginY - blockHeight);
				glVertex2f(beginX + blockWidth, beginY - blockHeight);
				glEnd();
			}

			else if (maze[i][j] == '@')
			{
				Player::Display(beginX, beginY, blockWidth, blockHeight);
			}

			else if (maze[i][j] == 'X')
			{
				glBegin(GL_QUADS);
				glColor3f(0.0f, 0.39218f, 0.0f);
				glVertex2f(beginX + blockWidth, beginY);
				glVertex2f(beginX, beginY);
				glVertex2f(beginX, beginY - blockHeight);
				glVertex2f(beginX + blockWidth, beginY - blockHeight);
				glEnd();
			}

			else if (maze[i][j] == '*')
			{
				Troll::Display(beginX, beginY, blockWidth, blockHeight);
			}

			else if (maze[i][j] == '&')
			{
				Weapon::Display(beginX, beginY, blockWidth, blockHeight);
			}

			else if (maze[i][j] == 's')
			{
				SpeedBooster::Display(beginX, beginY, blockWidth, blockHeight);
			}

			else if (maze[i][j] == '!')
			{
				PhasableBlock::Display(beginX, beginY, blockWidth, blockHeight);
			}

			else if (maze[i][j] == 'F')
			{
				FieryBlock::Display(beginX, beginY, blockWidth, blockHeight, a);
				a++;
			}

			else if (maze[i][j] == 'T')
			{
				Teleport::Display(beginX, beginY, blockWidth, blockHeight, b);
				b++;
			}

			beginX += blockWidth;
		}
		beginY -= blockHeight;
		beginX = -0.9f;
	}
	glFlush();
}

void display_Home()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutFullScreen();
	double blockWidth = 2.0 / 61.0;
	double blockHeight = 1.5 / 34.0;
	char buf1[] = "Welcome to Maze Runner!";
	renderbitmap(-0.8f, 0.85f - 0.05f, GLUT_BITMAP_9_BY_15, buf1);
	char buf2[] = "For the sake of the game, you, my friend, are a weird looking green creature still unknown to mankind";
	renderbitmap(-0.8f, 0.75f - 0.05f, GLUT_BITMAP_9_BY_15, buf2);
	char buf21[] = "Right now, you're stuck in a maze and your task is to get out of it alive";
	renderbitmap(-0.8f, 0.65f - 0.05f, GLUT_BITMAP_9_BY_15, buf21);
	char buf212[] = "You look something like this -> ";
	renderbitmap(-0.8f, 0.55f - 0.05f, GLUT_BITMAP_9_BY_15, buf212);
	Player::Display(-0.5f, 0.58f - 0.05f, blockWidth, blockHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf3[] = "Use the arrow keys to move up, down, right or left ";
	renderbitmap(-0.8f, 0.45f - 0.05f, GLUT_BITMAP_9_BY_15, buf3);
	char buf4[] = "Watch out for the red coloured TROLLS that look like this ->      They are trying to kill you. (don't let them stop you :P)";
	renderbitmap(-0.8f, 0.35f - 0.05f, GLUT_BITMAP_9_BY_15, buf4);
	Troll::Display(-0.227f, 0.38f - 0.05f, blockWidth, blockHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf5[] = "There will be some WEAPONS, which look like this ->      and SPEED BOOSTERS, which look like this ->     ";
	renderbitmap(-0.8f, 0.25f - 0.05f, GLUT_BITMAP_9_BY_15, buf5);
	Weapon::Display(-0.315f, 0.282f - 0.05f, blockWidth, blockHeight);
	SpeedBooster::Display(0.15f, 0.282f - 0.05f, blockWidth, blockHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf51[] = "We put them to help you get out of the maze";
	renderbitmap(-0.8f, 0.15f - 0.05f, GLUT_BITMAP_9_BY_15, buf51);
	char buf6[] = "The Speedbooster increases the player's speed. You can use a weapon to kill only one troll (don't be too greedy smh) ";
	renderbitmap(-0.8f, 0.05f - 0.05f, GLUT_BITMAP_9_BY_15, buf6);
	char buf7[] = "At any instant, you can have either a weapon or a speedbooster, but not both";
	renderbitmap(-0.8f, -0.05f - 0.05f, GLUT_BITMAP_9_BY_15, buf7);
	char buf8[] = "There are certain blocks in the maze that are brownish like this ->      These are phasable walls which you can pass through only once (like Flash :D)";
	renderbitmap(-0.8f, -0.15f - 0.05f, GLUT_BITMAP_9_BY_15, buf8);
	PhasableBlock::Display(-0.16f, -0.12f - 0.05f, blockWidth, blockHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf81[] = "There are certain orangish glowing blocks like this ->      These are fiery walls. You go even near them, and boom! you're dead";
	renderbitmap(-0.8f, -0.25f - 0.05f, GLUT_BITMAP_9_BY_15, buf81);
	FieryBlock::Display(-0.285f, -0.222f - 0.05f, blockWidth, blockHeight, 1);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf811[] = "Then there are places like this in the maze ->     These are teleporting locations. (The pairing of these locations is random XD)";
	renderbitmap(-0.8f, -0.35f - 0.05f, GLUT_BITMAP_9_BY_15, buf811);
	Teleport::Display(-0.365f, -0.322f - 0.05f, blockWidth, blockHeight, 1);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf9[] = "The Exits will look like this ->       Press ENTER to start the game";
	renderbitmap(-0.8f, -0.45f - 0.05f, GLUT_BITMAP_9_BY_15, buf9);
	ExtraExits::Display(-0.47f - 0.02f, -0.42f - 0.05f, blockWidth, blockHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	char buf10[] = "All the best! :\")";
	renderbitmap(-0.8f, -0.55f - 0.05f, GLUT_BITMAP_9_BY_15, buf10);
	char buf11[] = "NOTE : Pls dont let us down. Plis. Get out alive.";
	renderbitmap(-0.8f, -0.65f - 0.05f, GLUT_BITMAP_9_BY_15, buf11);
	char buf12[] = "(Also.. you can press Esc and quit the game anytime)";
	renderbitmap(-0.8f, -0.75f - 0.05f, GLUT_BITMAP_9_BY_15, buf12);
	glFlush();
	glutPostRedisplay();
}

void display()
{
	if (GameBegin == 0)
	{
		display_Home();
	}
	else if (GameCompletion == 0 && GameBegin == 1)
	{
		glFlush();
		glutPostRedisplay();
		display_maze();
	}
	else if (GameCompletion == 1 && GameBegin == 1)
	{

		usleep(50000);
		display_WIN();
	}
	else if (GameCompletion == -1 && GameBegin == 1)
	{

		usleep(50000);
		display_LOSE();
	}
}
