#pragma once
#include "Vector2.h"
struct Wall
{
	Wall(Vector2 start, Vector2 end, string texture);
	Vector2 Start;
	Vector2 End;
	string Texture;
	Vector2 GetNormal();
	float Length();
};

