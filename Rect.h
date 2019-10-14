#pragma once
#include "Vector2.h"
struct Rect
{
	Rect(Vector2 position, Vector2 size);
	Rect(float x, float y, float width, float height);
	static Rect BoundingRect(Vector2 a, Vector2 b, Vector2 c);
	bool Contains(Vector2 point);
	Vector2 Position;
	Vector2 Size;
};

