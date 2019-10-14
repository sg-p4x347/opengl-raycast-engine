#include "pch.h"
#include "Rect.h"

Rect::Rect(Vector2 position, Vector2 size) : Position(position), Size(size)
{
}

Rect::Rect(float x, float y, float width, float height) : Rect::Rect(Vector2(x,y), Vector2(width,height))
{
}

Rect Rect::BoundingRect(Vector2 a, Vector2 b, Vector2 c)
{
	Vector2 min(std::min(a.X, std::min(b.X, c.X)), std::min(a.Y, std::min(b.Y, c.Y)));
	Vector2 max(std::max(a.X, std::max(b.X, c.X)), std::max(a.Y, std::max(b.Y, c.Y)));
	return Rect(min, max - min);
}

bool Rect::Contains(Vector2 point)
{
	return point.X >= Position.X && point.X <= Position.X + Size.X && point.Y >= Position.Y && point.Y <= Position.Y + Size.Y;
}
