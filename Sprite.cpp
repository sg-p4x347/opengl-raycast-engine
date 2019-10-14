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
	WallContacts.clear();
	// Update position, taking into account wall collisions
	Vector2 lateralImpulse = Vector2(Impulse.X, Impulse.Z);
	Vector2 deltaPos = lateralImpulse * elapsed;
	if (lateralImpulse.LengthSquared() > 0.f) {
		Vector2 mapPosition = GetMapPosition();
		
		for (auto& wall : world->GetWallsInRange(mapPosition, Radius)) {
			if (wall->Collision) {
				Vector2 futurePos = mapPosition + deltaPos;
				Vector2 walToSprite = GetVectorToSegment(wall->Start, wall->End, futurePos);

				float distance = walToSprite.Length();
				float penetration = std::max(0.f, Radius - distance);
				if (penetration > 0.f) {
					WallContacts.push_back(wall);
					deltaPos += (walToSprite.Normalized() * penetration); // correct the delta pos so as not to penetrate the wall
				}
			}
		}
		// Apply the corrected deltaPos
		Displace(Vector3(deltaPos.X, 0.f, deltaPos.Y));
	}
	SpriteContacts.clear();

	for (auto& otherSprite : world->GetSpritesInRange(GetMapPosition(),Radius)) {
		SpriteContacts.push_back(otherSprite);
	}
}

Vector2 Sprite::GetMapPosition()
{
	return Vector2(Position.X,Position.Z);
}
