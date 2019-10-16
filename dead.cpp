#include <iostream>
#include <GL/glut.h>			
using namespace std;

void drawAxis()
{
	glColor3f(1, 0, 0);			 // change drawing color to red
	glBegin(GL_POINTS);	            // use points to form X-/Y-axes
	for (int x = -150; x <= 150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y = -150; y <= 150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

}
//***************************************************************************************
GLubyte skull[] = {
	0x00, 0x00, 0x00, 0x00,
	0x0e, 0x00, 0x01, 0xc0,
	0x1f, 0x00, 0x03, 0xc0,
	0x1f, 0x0f, 0xc7, 0xe0,
	0x7f, 0x9f, 0xe7, 0xf8,			//5
	0x7f, 0x9f, 0xe7, 0xf8,			
	0x7f, 0xff, 0xff, 0xf8,
	0x3f, 0xff, 0xff, 0xf0,
	0x03, 0xf8, 0x3f, 0x00,			
	0x03, 0xf8, 0x7f, 0x00,			//10
	0x03, 0xf8, 0x7f, 0x00,
	0x03, 0x07, 0x83, 0x00,
	0x03, 0x03, 0x03, 0x00,
	0x07, 0x03, 0x03, 0x00,			
	0x07, 0x03, 0x03, 0x00,			//15
	0x0f, 0x03, 0x03, 0x00,
	0x0f, 0x03, 0x03, 0x00,
	0x0f, 0xff, 0xff, 0xc0,			
	0x0f, 0xff, 0xff, 0xc0,
	0x0f, 0xff, 0xff, 0xc0,			//20
	0x0f, 0xff, 0xff, 0x80,
	0x07, 0xff, 0xff, 0x80,
	0x3f, 0xff, 0xff, 0xf0,			
	0x7f, 0xff, 0xff, 0xf8,
	0x7f, 0xff, 0xff, 0xf8,			//25
	0x7f, 0xff, 0xff, 0xf0,
	0x3f, 0x0f, 0xc7, 0xf0,
	0x0f, 0x00, 0x03, 0xc0,			
	0x0f, 0x00, 0x01, 0xc0,
	0x00, 0x00, 0x00, 0x00			//30

};

//**************************************************************************************
void glBitmap() {
	glColor3f(0, 0, 0);
	glRasterPos2f(0, 0);
	glBitmap(30, 30, 30.0, 30.0, 0, 0.0, skull);

	glRasterPos2f(-70, 10);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');


}
//***************************************************************************************
void myInit()
{
	glClearColor(1, 0, 0, 1);			// background color: red 
	gluOrtho2D(-200, 200, -200, 200);  // viewing area
}
//***************************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(1.0, 1.0, 1.0);		//background color set to red
   
	drawAxis();
    glBitmap();
	glFlush(); 
	glutPostRedisplay();
}
//****************************************************************************************
int main(int argc, char** argv)
{
	glutInitWindowSize(400, 400);				// window size
	glutInitWindowPosition(100, 0);			    // window position
	glutCreateWindow("OH NO, YOU DIED!");	    // title

	myInit();									// setting up
	
	glutDisplayFunc(myDisplayCallback);		    // register a callback

	glutMainLoop();							    // get into an infinite loop

	return 0;
}
