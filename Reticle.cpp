#include "pch.h"
#include "Reticle.h"

Reticle::Reticle()
{
	activeItem = "Pistol";
}

void Reticle::renderReticle()
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	switch (Reticle::reticleMap.at(activeItem)) {
	case 0:
		//draw unique reticle for fists
		break;
	case 1:
		//draw unique reticle for knife
		break;
	case 2: //Pistol
		for (double theta = 0; theta < 2 * M_PI; theta += (1.0 / (360.0 * 4)) * M_PI) {
			glVertex2d(cos(theta) + GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2 * sin(theta));
		}
		break;
	case 3: //Key
		for (double theta = 0; theta < 2 * M_PI; theta += (1.0 / 360.0) * M_PI) {
			glVertex2d(cos(theta) + GLUT_WINDOW_WIDTH / 2, sin(theta) + GLUT_WINDOW_HEIGHT / 2);
		}
		break;
	default:
		for (double theta = 0; theta < 2 * M_PI; theta += (1.0 / (360.0 * 4)) * M_PI) {
			glVertex2d(cos(theta) + GLUT_WINDOW_WIDTH / 2, GLUT_WINDOW_HEIGHT / 2 * sin(theta));
		}
		break;
	}
	glEnd();
}

void Reticle::updateActiveItem(string active)
{
	activeItem = active;
}
