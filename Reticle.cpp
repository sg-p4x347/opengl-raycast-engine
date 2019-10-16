#include "pch.h"
#include "Reticle.h"

Reticle::Reticle()
{
	activeItem = "Pistol";
}

void Reticle::renderReticle(int windowWidth, int windowHeight, float percentage)
{
	glColor3f(1, 0, 0);
	/******************************************************
	CIRCLE
	******************************************************/
	glBegin(GL_POINTS);
	float width = 64.f;
	float height = width;// windowHeight / 2.f;
	for (double theta = 0; theta < percentage * 2 * M_PI; theta += (1.0 / (360.0 * 4)) * M_PI) {
		glVertex2d(width * cos(theta) + windowWidth / 2, height * sin(theta) + windowHeight / 2.5f);
	}
	glEnd();
}

void Reticle::updateActiveItem(string active)
{
	activeItem = active;
}
