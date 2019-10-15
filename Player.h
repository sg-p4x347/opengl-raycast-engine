#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Agent.h"
#include "HUD.h"
class World;
class Player : public Agent
{
public:
	Player(Vector3 position, float angle, float fov, float nearPlane, float farPlane, float speed, float radius);
	virtual void Displace(Vector3 displacement) override;
	virtual void Update(double& elapsed, World * world) override;
	
	float NearPlane;
	float FarPlane;
	bool RangedAttack;

	float FOV;
	float Displacement;
	map<string,int> Inventory;

	HUD hud;
};

