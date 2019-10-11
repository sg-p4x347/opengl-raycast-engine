#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Item.h"
Player::Player(
	Vector3 position, 
	float angle, 
	float fov,
	float nearPlane,
	float farPlane, 
	float speed,
	float radius
) : Sprite::Sprite(position, radius),
	Angle(angle), 
	FOV(fov),
	NearPlane(nearPlane), 
	FarPlane(farPlane),
	Speed(speed),
	Displacement(0.f)
{
}

Vector2 Player::GetHeading()
{
	return Vector2(std::cos(Angle), std::sin(Angle));
}

void Player::Displace(Vector3 displacement)
{
	Sprite::Displace(displacement);
	Displacement += displacement.Length();
	Position.Y = 0.5 + 0.01 * std::sin(Displacement * 10.f);
}

void Player::Update(double& elapsed, World * world)
{
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

	Sprite::Update(elapsed, world);

	for (auto& sprite : SpriteContacts) {
		if ((Item*)sprite.get()) {
			Inventory[sprite->Texture]++;
			world->RemoveSprite(sprite);
		}
	}
}
