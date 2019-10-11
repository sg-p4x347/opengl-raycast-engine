#pragma once
#include "Vector3.h"
class Sprite
{
public:
	Sprite();
	Sprite(Vector3 position, float radius, string texture = "");
	Vector3 Position;
	Vector3 Impulse;
	float Radius;
	string Texture;
private:

};

