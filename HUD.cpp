#include "HUD.h"

HUD::HUD()
{
	
}

HUD::HUD(map<string, int> & Inv)
{
	Inventory = Inv;
}

void HUD::render()
{
	addReticle();
	bottomBackground();
	addTiles();
}

void HUD::addReticle()
{
	reticle.renderReticle();
}

void HUD::bottomBackground()
{
	glColor3f(115.0 / 255.0, 111.0 / 255.0, 101.0 / 255.0);

	glBegin(GL_POLYGON);

	glVertex2d(0, sizeOfBottom);
	glVertex2d(GLUT_WINDOW_WIDTH, sizeOfBottom);
	glVertex2d(GLUT_WINDOW_WIDTH, 0);
	glVertex2d(0, 0);

	glEnd();

	glColor3f(1, 1, 1);
	glLineWidth(5);
	glBegin(GL_LINES);

	//Top bar
	glVertex2d(0, sizeOfBottom + yPadding / 2);
	glVertex2d(GLUT_WINDOW_WIDTH, sizeOfBottom + yPadding / 2);

	glEnd();
}

void HUD::addTiles()
{
	glColor3f(0, 0, 0);

	int max = 5;
	for (int i = 0; i < max; ++i) {
		glBegin(GL_POLYGON);

		glVertex2d(i * GLUT_WINDOW_WIDTH / max + xPadding / 2, sizeOfBottom - yPadding / 2);
		glVertex2d((i + 1) * GLUT_WINDOW_WIDTH / max - xPadding / 2, sizeOfBottom - yPadding / 2);
		glVertex2d((i + 1) * GLUT_WINDOW_WIDTH / max - xPadding / 2, yPadding / 2);
		glVertex2d(i * GLUT_WINDOW_WIDTH / max + xPadding / 2, yPadding / 2);

		glEnd();
	}

	
}
