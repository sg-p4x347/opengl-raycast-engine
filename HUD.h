#pragma once
#include "pch.h"
#include "Reticle.h"

class HUD
{
public:
	float sizeOfBottom = 0.15 * GLUT_WINDOW_HEIGHT;
	float yPadding = 0.01 * GLUT_WINDOW_HEIGHT;
	float xPadding = 0.01 * GLUT_WINDOW_WIDTH;

	map<string, int> Inventory;
	Reticle reticle;

	HUD();
	HUD(map<string, int> & Inv);

	void render();

private:
	void addReticle();
	void bottomBackground();
	void addTiles();
};

