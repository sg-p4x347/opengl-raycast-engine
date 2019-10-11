#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Sprite.h"
class Player : public Sprite
{
public:
	Player(Vector3 position, float angle, float fov, float nearPlane, float farPlane, float speed, float radius);
	Vector2 GetHeading();
	void Move(Vector2 displacement);
	float Angle;
	float NearPlane;
	float FarPlane;
	float Speed;
	float FOV;
	float Displacement;
};

