#include "pch.h"
#include "HUD.h"

HUD::HUD()
{
	set<string> possibleIcons = {
		"standardDude.bmp"
	};

	for (string icon : possibleIcons) {
		Icons.insert({ icon, Icon() });
		Icons[icon].fileHandler(icon);
	}

}

void HUD::setInventory(map<string, int> inv)
{
	Inventory = inv;
}

void HUD::render()
{
	float sizeOfBottom = 0.15 * GLUT_WINDOW_HEIGHT;
	float yPadding = 0.01 * GLUT_WINDOW_HEIGHT;
	float xPadding = 0.01 * GLUT_WINDOW_WIDTH;

	addReticle();
	bottomBackground(sizeOfBottom, yPadding, xPadding);
	addTiles(sizeOfBottom, yPadding, xPadding);
	//addIcons(sizeOfBottom, yPadding, xPadding);
}

void HUD::addReticle()
{
	reticle.renderReticle();
}

void HUD::bottomBackground(float& sizeOfBottom, float& yPadding, float& xPadding)
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
	glVertex2d(0, sizeOfBottom + (yPadding / 2.0));
	glVertex2d(GLUT_WINDOW_WIDTH, sizeOfBottom + (yPadding / 2.0));

	glEnd();
}

void HUD::addTiles(float& sizeOfBottom, float& yPadding, float& xPadding)
{
	glColor3f(0, 0, 0);

	int max = 5;
	for (int i = 0; i < max; ++i) {
		glBegin(GL_POLYGON);

		glVertex2d(i * GLUT_WINDOW_WIDTH / max + (xPadding / 2.0), sizeOfBottom - (yPadding / 2.0));
		glVertex2d((i + 1) * GLUT_WINDOW_WIDTH / max - (xPadding / 2.0), sizeOfBottom - (yPadding / 2.0));
		glVertex2d((i + 1) * GLUT_WINDOW_WIDTH / max - (xPadding / 2.0), yPadding / 2.0);
		glVertex2d(i * GLUT_WINDOW_WIDTH / max + (xPadding / 2.0), yPadding / 2.0);

		glEnd();
	}
}

void HUD::addIcons(float& sizeOfBottom, float& yPadding, float& xPadding)
{
	int tileNumber = 0;
	for (auto icon : Icons) {
		glBegin(GL_BITMAP);

		glRasterPos2d(0, 0);
		glDrawPixels(Icon::WIDTH, Icon::HEIGHT, GL_RGB, GL_FLOAT, (GLvoid*)Icons[icon.first].imagePixels);

		glEnd();
	}
}
