#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Item.h"
#include "Door.h"
#include "Bullet.h"

Player::Player(
	Vector3 position,
	float angle,
	float fov,
	float nearPlane,
	float farPlane,
	float speed,
	float radius
) : Agent::Agent(position, radius,speed,1.f,2.f),
FOV(fov),
NearPlane(nearPlane),
FarPlane(farPlane),
Displacement(0.f)
{
	MeleeCooldown = 1.f;
	MeleeDamage = 1.f;
	hud.setInventory(Inventory);
}
void Player::Displace(Vector3 displacement)
{
	Sprite::Displace(displacement);
	Displacement += displacement.Length();
	Position.Y = 0.5 + 0.01 * std::sin(Displacement * 10.f);
}

void Player::Update(double& elapsed, World* world)
{
	Agent::Update(elapsed, world);
	if (Health > 0.f) {
		MeleeAttack = world->m_buttonStates[GLUT_LEFT_BUTTON];

		float deltaRotation = 0.f;
		deltaRotation -= world->GetMouseDelta().X * 0.005f;
		Angle += deltaRotation;
		world->ResetMouseDelta();
		Vector2 inputDir;
		if (world->m_keyStates['a']) {
			inputDir.X -= 1.f;
		}
		if (world->m_keyStates['d']) {
			inputDir.X += 1.f;
		}
		
		if (world->m_keyStates['w']) {
			inputDir.Y += 1.f;
		}
		if (world->m_keyStates['s']) {
			inputDir.Y -= 1.f;
		}
		if (inputDir.LengthSquared() > 0.f) {
			inputDir = inputDir.Normalized();
			Vector2 heading = GetHeading();
			Vector2 impulse = (heading * inputDir.Y + heading.Right() * inputDir.X) * Speed;
			
			Impulse = Vector3(impulse.X, 0.f, impulse.Y);
		}
		else {
			Impulse = Vector3();
		}



		// Pick up items
		for (auto& sprite : SpriteContacts) {
			shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(sprite);
			if (item) {
				Inventory[item->Texture]++;
				world->RemoveSprite(item);
			}
		}
		// Unlock doors
		for (auto& wall : WallContacts) {
			shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(wall);
			if (door && Inventory[door->Key] > 0) {
				// Unlock and open the door
				door->Open = true;
			}
		}
		if (world->m_buttonStates[GLUT_RIGHT_BUTTON]) {
			if (!RangedAttack) {
				RangedAttack = true;
				// Spawn a bullet
				float bulletRadius = 0.05f;
				Vector2 bulletPos = GetMapPosition() + GetHeading() * (Radius + bulletRadius + 0.001f);
				Vector3 velocity = Vector3(GetHeading().X, 0.f, GetHeading().Y) * 20.f;
				world->AddSprite(std::make_shared<Bullet>(Vector3(bulletPos.X, Position.Y, bulletPos.Y), velocity, bulletRadius, 1.f, "bird_shot.bmp"));
			}
		}
		else {
			RangedAttack = false;
		}
	}
}
