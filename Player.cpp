#include "pch.h"
#include "Player.h"


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

void Player::Move(Vector2 displacement)
{
	Position += Vector3(displacement.X, 0.f, displacement.Y);
	Displacement += displacement.Length();
	Position.Y = 0.5 + 0.01 * std::sin(Displacement * 20.f);
}
