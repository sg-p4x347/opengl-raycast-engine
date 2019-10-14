#pragma once
#include "pch.h"
#include "AnimatedWall.h"
struct Door : public AnimatedWall
{
	Door(Vector2 start, Vector2 end, string texture, string key, Vector2 speed, bool open);
	string Key;
	bool Open;
	virtual void Update(double& elapsed, World* world) override;
};

