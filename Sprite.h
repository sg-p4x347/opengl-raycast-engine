#pragma once
#include "Vector3.h"
class World;
class Sprite
{
public:
	Sprite();
	Sprite(Vector3 position, float radius, string texture = "");
	Vector3 Position;
	Vector3 Impulse;
	float Radius;
	string Texture;
	vector<shared_ptr<Sprite>> SpriteContacts;
	virtual void Displace(Vector3 displacement);
	virtual void Update(double& elapsed, World* world);
private:

};

