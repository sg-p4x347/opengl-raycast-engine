#pragma once
#include "Wall.h"
class World;
struct AnimatedWall : public Wall
{
	AnimatedWall(Vector2 start, Vector2 end, string texture, Vector2 speed);
	Vector2 Speed;
	virtual void Update(double& elapsed, World* world);
};

