#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Item.h"
#include "Door.h"
Player::Player(
	Vector3 position,
	float angle,
	float fov,
	float nearPlane,
	float farPlane,
	float speed,
	float radius
) : Agent::Agent(position, radius,speed,1.f,2.f),
FOV(fov),
NearPlane(nearPlane),
FarPlane(farPlane),
Displacement(0.f)
{
	MeleeCooldown = 1.f;
	MeleeDamage = 1.f;
}
void Player::Displace(Vector3 displacement)
{
	Sprite::Displace(displacement);
	Displacement += displacement.Length();
	Position.Y = 0.5 + 0.01 * std::sin(Displacement * 10.f);
}

void Player::Update(double& elapsed, World* world)
{
	Agent::Update(elapsed, world);
	if (Health > 0.f) {
		MeleeAttack = world->m_buttonStates[GLUT_LEFT_BUTTON];

		float deltaRotation = 0.f;
		if (world->m_keyStates['a']) {
			deltaRotation += 0.1f;
		}
		if (world->m_keyStates['d']) {
			deltaRotation += -0.1f;
		}
		Angle += deltaRotation;

		float forwardSpeed = 0.f;
		if (world->m_keyStates['w']) {
			forwardSpeed += Speed;
		}
		if (world->m_keyStates['s']) {
			forwardSpeed += -Speed;
		}
		Vector2 heading = GetHeading();
		Impulse = Vector3(heading.X, 0.f, heading.Y) * forwardSpeed;



		// Pick up items
		for (auto& sprite : SpriteContacts) {
			shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(sprite);
			if (item) {
				Inventory[item->Texture]++;
				world->RemoveSprite(item);
			}
		}
		// Unlock doors
		for (auto& wall : WallContacts) {
			shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(wall);
			if (door && Inventory[door->Key] > 0) {
				// Unlock and open the door
				door->Open = true;
			}
		}
	}
}
