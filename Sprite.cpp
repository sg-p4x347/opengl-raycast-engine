#include "pch.h"
#include "Sprite.h"
#include "World.h"
#include "Utility.h"

Sprite::Sprite() : Sprite::Sprite(Vector3(), 0.f)
{
}

Sprite::Sprite(Vector3 position, float radius, string texture) : Position(position), Radius(radius), Texture(texture)
{
}

void Sprite::Displace(Vector3 displacement)
{
	Position += displacement;
}

void Sprite::Update(double& elapsed, World* world)
{
	// Update position, taking into account wall collisions
	Vector2 lateralImpulse = Vector2(Impulse.X, Impulse.Z);
	Vector2 deltaPos = lateralImpulse * elapsed;
	Vector2 spritePos(Position.X, Position.Z);
	Vector2 futurePos = spritePos + deltaPos;
	for (auto& wall : world->m_walls) {

		Vector2 walToSprite = GetVectorToSegment(wall.Start, wall.End, futurePos);


		float distance = walToSprite.Length();
		float penetration = std::max(0.f, Radius - distance);
		deltaPos += walToSprite.Normalized() * penetration; // correct the delta pos so as not to penetrate the wall

	}
	// Apply the corrected deltaPos
	Displace(Vector3(deltaPos.X, 0.f, deltaPos.Y));

	SpriteContacts.clear();
	Vector2 mapPosition(Position.X, Position.Z);
	for (auto& otherSprite : world->m_sprites) {
		if (this != otherSprite.get()) {
			float radialSum = Radius + otherSprite->Radius;
			if ((mapPosition - Vector2(otherSprite->Position.X, otherSprite->Position.Z)).LengthSquared() <= radialSum * radialSum) {
				SpriteContacts.push_back(otherSprite);
			}
		}
	}
}
