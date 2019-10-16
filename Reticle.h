#pragma once
#include "pch.h"

class Reticle
{
public:
	string activeItem;
	Reticle();
	void renderReticle(int windowWidth, int windowHeight, float percentage);
	void updateActiveItem(string active);
};

