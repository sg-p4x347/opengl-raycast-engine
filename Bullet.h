#pragma once
#include "pch.h"
#include "Agent.h"
class World;
class Bullet : public Agent
{
public:
	Bullet(Vector3 position, Vector3 velocity,float radius, float damage, string texture);
	virtual void Update(double& elapsed, World* world);
	float Damage;
};

