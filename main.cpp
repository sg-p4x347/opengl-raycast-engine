/*-----------------------------------------------------------------------------------------
 COURSE:				CSC525 lab8
 PROGRAMMERS:			Gage Coates (Coates347)
 MODIFIED BY:			Gage Coates (Coates347)
 DATE MODIFIED:			10/2/2019

 FOLDER:				Coates347
 DESCRIPTION:			Lab8: read a color bitmap from file and render it to the screen
 NOTE:					N/A
 FILES:					bitmap.cpp
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
void keyHandler(unsigned char key, int x, int y);
void keyUpHandler(unsigned char key, int x, int y);
void windowChangeHandler(int width, int height);
World world;

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	// specify a window size
	glutInitWindowSize(600, 600);
	// specify a window position
	glutInitWindowPosition(100, 0);
	// create a titled window
	glutCreateWindow("Project 1");	
	// setting up
	initialize();
	// register a callback
	glutDisplayFunc(render);
	glutPassiveMotionFunc(mouseMoveHandler);
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
	gluOrtho2D(-300, 300, -300, 300); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	world.UpdateBackBuffer(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

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
