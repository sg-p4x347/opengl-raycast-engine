#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Agent.h"
class World;
class Player : public Agent
{
public:
	Player(Vector3 position, float angle, float fov, float nearPlane, float farPlane, float speed, float radius);
	virtual void Displace(Vector3 displacement) override;
	virtual void Update(double& elapsed, World * world) override;
	
	float NearPlane;
	float FarPlane;
	
	float FOV;
	float Displacement;
	map<string,int> Inventory;
private:
	Vector2 m_mouseDelta;
	Vector2 m_lastMousePos;
};

