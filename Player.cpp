#include "pch.h"
#include "Player.h"


Player::Player(Vector3 position, float angle, float fov, float nearPlane, float farPlane, float speed) :
	m_position(position), 
	m_angle(angle), 
	m_fov(fov),
	m_nearPlane(nearPlane), 
	m_farPlane(farPlane),
	m_speed(speed),
	m_displacement(0.f)
{
}

Vector3 Player::GetPosition()
{
	return m_position;
}

void Player::SetPosition(Vector3 pos)
{
	m_position = pos;
}

Vector2 Player::GetHeading()
{
	return Vector2(std::cos(m_angle), std::sin(m_angle));
}

float Player::GetAngle()
{
	return m_angle;
}

void Player::SetAngle(float angle)
{
	m_angle = angle;
}

float Player::GetNearPlane()
{
	return m_nearPlane;
}

float Player::GetFOV()
{
	return m_fov;
}

float Player::GetSpeed()
{
	return m_speed;
}

void Player::Move(Vector2 displacement)
{
	m_position += Vector3(displacement.X, 0.f, displacement.Y);
	m_displacement += displacement.Length();
	m_position.Y = 0.5 + 0.01 * std::sin(m_displacement * 20.f);
}
