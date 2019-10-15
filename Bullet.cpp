#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Vector3 position, Vector3 velocity, float radius, float damage, string texture) :
	Agent::Agent(position,radius,0.f,damage,0.f,texture),
	Damage(damage)
{
	Impulse = velocity;
}

void Bullet::Update(double& elapsed, World* world)
{
	Agent::Update(elapsed, world);
	for (auto& sprite : SpriteContacts) {
		auto agent = std::dynamic_pointer_cast<Agent>(sprite);
		if (agent) {
			// Hit
			agent->ApplyDamage(Damage);
			break;
		}
	}
	if (!SpriteContacts.empty() || !WallContacts.empty()) {
		// Kill the bullet if it hits anything
		ApplyDamage(Damage);
	}
}
