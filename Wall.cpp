#include "pch.h"
#include "Wall.h"

Wall::Wall(Vector2 start, Vector2 end, string texture) : Start(start), End(end), Texture(texture)
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
