#include "pch.h"
#include "Door.h"

Door::Door(Vector2 start, Vector2 end, string texture, string key, Vector2 speed, bool open) :
	AnimatedWall::AnimatedWall(start, end, texture, speed),
	Key(key),
	Open(open)
{
	WrapTextureY = false;
}

void Door::Update(double& elapsed, World* world)
{
	Speed.Y = (Open ? std::abs(Speed.Y) : -std::abs(Speed.Y));
	AnimatedWall::Update(elapsed, world);
	static const float maxOpenPercent = 0.6f;

	TextureSampleOffset.Y = std::min(0.f, std::max(-maxOpenPercent, TextureSampleOffset.Y));
	float openPercent = -TextureSampleOffset.Y / maxOpenPercent;
	// Update the alpha property for efficient and correct rendering
	Alpha = openPercent > 0.f;

	// Update the collision so open doors can be passed through
	if (openPercent == 1.f) {
		Collision = false;
	}

}
