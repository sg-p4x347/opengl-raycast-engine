#pragma once
#include "Vector2.h"
#include "Vector3.h"
class Player
{
public:
	Player(Vector3 position, float angle, float fov, float nearPlane, float farPlane, float speed);
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	Vector2 GetHeading();
	float GetAngle();
	void SetAngle(float angle);
	float GetNearPlane();
	float GetFOV();
	float GetSpeed();
	void Move(Vector2 displacement);
private:
	Vector3 m_position;
	float m_angle;
	float m_fov;
	float m_nearPlane;
	float m_farPlane;
	float m_speed;
	float m_displacement;
};

