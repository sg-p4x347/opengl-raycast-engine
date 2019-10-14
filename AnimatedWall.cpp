#include "pch.h"
#include "AnimatedWall.h"

AnimatedWall::AnimatedWall(Vector2 start, Vector2 end, string texture, Vector2 speed) :
	Wall::Wall(start,end,texture),
	Speed(speed)
{
	WrapTextureY = true;
	WrapTextureX = true;
}

void AnimatedWall::Update(double& elapsed, World* world)
{
	Wall::Update(elapsed, world);
	// Positive speed will animate the texture going "Up" and "Right", negative will go "Down" and "Left"
	TextureSampleOffset -= Speed * elapsed;
	// Wrap texture sampling
	TextureSampleOffset.X = std::fmod(TextureSampleOffset.X, 1.f);
	TextureSampleOffset.Y = std::fmod(TextureSampleOffset.Y, 1.f);
}
