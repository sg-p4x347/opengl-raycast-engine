#include "pch.h"
#include "Spider.h"
#include "World.h"
Spider::Spider(Vector3 position) : Agent::Agent(position, 0.25f,1.f,1.f,0.5f,"spider.bmp","dead_spider.bmp")
{
	MeleeDamage = 1.f;
	SpideySenseRange = 20.f;
	MeleeCooldown = 2.f;
	MeleeTimer = MeleeCooldown;
	MeleeAttack = true;
}

void Spider::Update(double& elapsed, World* world)
{
	
	auto player = world->GetPlayer();
	Vector2 toPlayer = player->GetMapPosition() - GetMapPosition();
	float distance = toPlayer.Length();
	if (distance <= SpideySenseRange) {
		Vector2 heading = toPlayer.Normalized();
		Angle = std::atan2f(heading.X, heading.Y);
		if (distance >= 0.1) {
			// Get closer
			Impulse = Vector3(heading.X, 0.f, heading.Y) * Speed;
			// Hold off attack until closer
			MeleeAttack = false;
		}
		//else if (distance < MeleeRange - 0.1f) {
		//	// Get farther (a fudge factor keeps from jittering)
		//	Impulse = -Vector3(heading.X, 0.f, heading.Y) * Speed;
		//	// Attack
		//	MeleeAttack = true;
		//}
		else {
			// Stop
			Impulse = Vector3();
			// Attack
			MeleeAttack = true;
		}
		
	}
	Agent::Update(elapsed, world);
}
