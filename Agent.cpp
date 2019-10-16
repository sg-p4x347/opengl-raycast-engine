#include "pch.h"
#include "Agent.h"
#include "Utility.h"
#include "World.h"
Agent::Agent(
	Vector3 position, 
	float radius, 
	float speed,
	float health,
	float meleeRange, 
	string texture,
	string deadTexture
) : Sprite::Sprite(position,radius,texture),
	Health(health),
	Speed(speed),
	Angle(0.f),
	DeadTexture(deadTexture),
	MeleeRange(meleeRange),
	Attack(false),
	MeleeDamage(0.f),
	AttackCooldown(1.f),
	AttackTimer(AttackCooldown)
{
}

void Agent::Update(double& elapsed, World* world)
{
	Sprite::Update(elapsed, world);

	if (Health > 0.f) {
		Vector2 mapPosition = GetMapPosition();
		if (Attack && AttackTimer >= AttackCooldown) {
			AttackTimer = 0.f;
			Vector2 attackEnd = mapPosition + GetHeading() * MeleeRange;
			for (auto& sprite : world->GetSpritesInRange(mapPosition, MeleeRange)) {
				if (&*sprite != this) {
					auto agent = std::dynamic_pointer_cast<Agent>(sprite);
					if (agent) {
						Vector2 attackToAgent = GetVectorToSegment(mapPosition, attackEnd, agent->GetMapPosition());
						if (attackToAgent.LengthSquared() <= agent->Radius * agent->Radius) {
							// A HIT!
							agent->Health -= MeleeDamage;
						}
					}
				}
			}
		}
	}
	else {
		// Replace this agent with a death sprite
		world->RemoveSprite(this);
		world->AddSprite(std::make_shared<Sprite>(Position, Radius, DeadTexture));
	}
	AttackTimer += elapsed;
}

Vector2 Agent::GetHeading()
{
	return Vector2(std::cos(Angle), std::sin(Angle));
}

void Agent::ApplyDamage(float damage)
{
	Health -= damage;
}
