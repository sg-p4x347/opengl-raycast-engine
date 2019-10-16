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
	void ApplyDamage(float damage);
	float Health;

	float MeleeRange;
	bool Attack;
	float MeleeDamage;
	float AttackCooldown;
	float AttackTimer;
	float DamageTimer;

	float Angle;
	float Speed;
	string DeadTexture;


};

