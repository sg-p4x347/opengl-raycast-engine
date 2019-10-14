#pragma once
#include "pch.h"
#include "Sprite.h"
#include "Wall.h"

struct Region
{
	Region();
	set<shared_ptr<Sprite>> Sprites;
	set<shared_ptr<Wall>> Walls;
};

