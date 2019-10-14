#pragma once
#include "Vector2.h"
class World;
struct Wall
{
	Wall(Vector2 start, Vector2 end, string texture);
	Vector2 Start;
	Vector2 End;
	string Texture;
	bool Alpha;
	bool Collision;
	Vector2 TextureSampleOffset;
	bool WrapTextureX;
	bool WrapTextureY;
	Vector2 GetNormal();
	float Length();
	virtual void Update(double& elapsed, World* world);
};

