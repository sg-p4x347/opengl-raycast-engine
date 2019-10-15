#pragma once
#include "pch.h"

class Reticle
{
public:
	string activeItem;
	const map<string, int> reticleMap = {
		{"Fist", 0},
		{"Knife", 1},
		{"Pistol", 2},
		{"Key", 3}
	};
	
	Reticle();
	void renderReticle();
	void updateActiveItem(string active);
};

