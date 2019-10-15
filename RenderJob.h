#pragma once
#include "Bitmap.h"
#include "Vector2.h"
struct RenderJob
{
	RenderJob(string texture,Vector2 start, Vector2 end, bool alpha, Vector2 textureSampleOffset, bool wrapTextureX, bool wrapTextureY);
	string Texture;
	Vector2 Start;
	Vector2 End;
	Vector2 Normal;
	float Length;
	bool Alpha;
	Vector2 TextureSampleOffset;
	bool WrapTextureX;
	bool WrapTextureY;
	double Depth;
};

