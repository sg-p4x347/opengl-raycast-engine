#pragma once
#include "pch.h"
#include "Sprite.h"
class Item : public Sprite
{
public:
	Item();
	Item(Vector3 position, float radius, string texture = "");
};

