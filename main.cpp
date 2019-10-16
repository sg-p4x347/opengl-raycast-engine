/*-----------------------------------------------------------------------------------------
 COURSE:				CSC525 Project 1
 PROGRAMMERS:			Gage Coates		(Coates347)
						Paul Durham		(Durham321)
						Anthony Harris	(Anthony999)
						Devlyn Hogue	(Hogue3)
 LAST MODIFIED:			10/16/2019
 DESCRIPTION:			Project 1. A simple Doom-esque game using raycasting and OpenGL.
 NOTE:					N/A
 IDE/COMPILER:			MicroSoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on labProject.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+F5					to EXECUTE
-----------------------------------------------------------------------------------------*/
#include "pch.h"
#include "World.h"

void initialize();
void gameTick(int value = 0);
void render();
void mouseMoveHandler(int cursorX, int cursorY);
void mouseButtonHandler(int button, int state, int x, int y);
void keyHandler(unsigned char key, int x, int y);
void keyUpHandler(unsigned char key, int x, int y);
void windowChangeHandler(int width, int height);
World world;

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	// specify a window position
	glutInitWindowPosition(0, 0);
	// specify a window size
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	
	// create a titled window
	glutCreateWindow("Project 1");	
	// setting up
	initialize();
	// register a callback
	glutDisplayFunc(render);
	glutPassiveMotionFunc(mouseMoveHandler);
	glutMotionFunc(mouseMoveHandler);
	glutMouseFunc(mouseButtonHandler);
	glutKeyboardFunc(keyHandler);
	glutKeyboardUpFunc(keyUpHandler);
	glutReshapeFunc(windowChangeHandler);
	gameTick();
	// get into an infinite loop
	glutMainLoop();
	return 0;
}

void initialize() {
	// specify a background clor: white
	glClearColor(0,0,0, 0);			
	// specify a viewing area
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	world.UpdateBackBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

}
void gameTick(int value)
{
	double elapsed = 0.0166666;
	
	world.Update(elapsed);
	render();
	glutTimerFunc(16, gameTick, 0);
}
void render() {
	// draw the background
	glClear(GL_COLOR_BUFFER_BIT);
	
	world.Render();
	
	// flush out the buffer contents
	glFlush(); 
}

void mouseMoveHandler(int cursorX, int cursorY)
{
	world.UpdateMousePosition(Vector2(cursorX, cursorY));
	
}

void mouseButtonHandler(int button, int state, int x, int y)
{
	world.UpdateButtonState(button, state == GLUT_DOWN);
}

void keyHandler(unsigned char key, int x, int y)
{
	world.UpdateKeyState(key, true);
}

void keyUpHandler(unsigned char key, int x, int y)
{
	world.UpdateKeyState(key, false);
}

void windowChangeHandler(int width, int height)
{
	world.UpdateBackBuffer(width, height);
}
