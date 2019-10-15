#pragma once
#include "pch.h"
#include "Reticle.h"
#include "Icon.h"

class HUD
{
public:
	map<string, Icon> Icons;
	map<string, int> Inventory;
	Reticle reticle;

	HUD();

	void setInventory(map<string, int> inv);
	void render();

private:
	void addReticle();
	void bottomBackground(float& sizeOfBottom, float& yPadding, float& xPadding);
	void addTiles(float& sizeOfBottom, float& yPadding, float& xPadding);
	void addIcons(float& sizeOfBottom, float& yPadding, float& xPadding);
};

