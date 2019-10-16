#pragma once
#include "pch.h"
#include "Reticle.h"
#include "Bitmap.h"
class Player;
class HUD
{
public:
	map<string, shared_ptr<Bitmap>> Icons;
	map<string, vector<uint8_t>> IconMasks;
	map<string, shared_ptr<Bitmap>> Views;

	Reticle reticle;

	HUD(Player * player);

	void render(int windowWidth, int windowHeight);

private:
	Player* m_player;
	void addReticle(int windowWidth, int windowHeight);
	void renderActiveItem(int windowWidth, int windowHeight);
	void renderFace(int windowWidth, int windowHeight);
	void bottomBackground(float& sizeOfBottom, float& yPadding, float& xPadding, int windowWidth, int windowHeight);
	void addTiles(float& sizeOfBottom, float& yPadding, float& xPadding, int windowWidth, int windowHeight);
};

