#include "pch.h"
#include "Wall.h"
#include "World.h"
Wall::Wall(Vector2 start, Vector2 end, string texture) :
	Start(start),
	End(end),
	Texture(texture),
	Collision(true),
	Alpha(false),
	WrapTextureX(true),
	WrapTextureY(false)
{
}

Vector2 Wall::GetNormal()
{
	return (End - Start).Right().Normalized();
}

float Wall::Length()
{
	return (End - Start).Length();
}

void Wall::Update(double& elapsed, World* world)
{
}
