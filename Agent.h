#pragma once
#include "pch.h"
#include "Sprite.h"
class World;
class Agent : public Sprite
{
public:
	Agent(Vector3 position, float radius, float speed, float health, float meleeRange, string texture = "", string deadTexture = "");
	virtual void Update(double& elapsed, World* world) override;
	Vector2 GetHeading();
	float Health;

	float MeleeRange;
	bool MeleeAttack;
	float MeleeDamage;
	float MeleeCooldown;
	float MeleeTimer;

	float Angle;
	float Speed;
	string DeadTexture;


};

