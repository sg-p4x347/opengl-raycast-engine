#include "pch.h"
#include "World.h"

const float World::MOUSE_GAIN = 0.1f;

World::World() : m_player(Vector3(0.f,0.5f,0.f), 0.f , 1.f, 0.1f, 1000.f, 4.f)
{
	m_floorColor = Pixel(26, 26, 26, 255);
	m_ceilingColor = Pixel(40, 40, 40, 255);
	/*m_walls.push_back(Wall(Vector2(-0.5f, 0.5f), Vector2(0.5f, 0.5f), "bricks_weathered.bmp"));
	m_walls.push_back(Wall(Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f), "bricks_mossy.bmp"));
	m_walls.push_back(Wall(Vector2(0.5f, -0.5f), Vector2(-0.5f, -0.5f), "bricks.bmp"));
	m_walls.push_back(Wall(Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.5f), "bricks.bmp"));
	m_walls.push_back(Wall(Vector2(-20.f, 10.f), Vector2(20.f, 10.f), "bricks_weathered.bmp"));*/

	m_sprites.push_back(Sprite(Vector3(10.5f, 0.f,9.5f), "key.bmp"));

	CreateWallPath(
		"bricks.bmp",
		vector<Vector2>{
			Vector2(9,8),
			Vector2(6,4),
			Vector2(0,4),
			Vector2(0,0),
			Vector2(20,0),
			Vector2(20,5),
			Vector2(18,7),
			Vector2(18,13),
			Vector2(13,13),
			Vector2(10,9)
		}
	);
	CreateWallPath(
		"bricks_mossy.bmp",
		vector<Vector2>{
		Vector2(9, 8),
			Vector2(0, 12),
			Vector2(0, 13),
			Vector2(10, 9)
	}
	);
}

void World::Update(double& elapsed)
{
	// Update player angle
	
	m_mouseDelta = Vector2(); // Consume the delta

	float deltaRotation = 0.f;
	if (m_keyStates['a']) {
		deltaRotation += 0.1f;
	}
	if (m_keyStates['d']) {
		deltaRotation += -0.1f;
	}
	m_player.SetAngle(m_player.GetAngle() + deltaRotation);

	float forwardSpeed = 0.f;
	if (m_keyStates['w']) {
		forwardSpeed += m_player.GetSpeed();
	}
	if (m_keyStates['s']) {
		forwardSpeed += -m_player.GetSpeed();
	}
	Vector2 displacement = m_player.GetHeading() * forwardSpeed * elapsed;
	m_player.Move(displacement);

}

void World::Render()
{
	std::lock_guard<mutex> lock(m_mutex);
	Vector2 playerPos = Vector2(m_player.GetPosition().X, m_player.GetPosition().Z);
	Vector2 playerHeading = m_player.GetHeading();
	Vector2 nearStart = playerPos + playerHeading.Left() * std::tan(m_player.GetFOV() * 0.5f) * m_player.GetNearPlane() + playerHeading * m_player.GetNearPlane();
	Vector2 nearEnd = playerPos + playerHeading.Right() * std::tan(m_player.GetFOV() * 0.5f) * m_player.GetNearPlane() + playerHeading * m_player.GetNearPlane();
	int visionWidth = m_backBuffer->GetWidth();
	int visionHeight = m_backBuffer->GetHeight();
	double floorPercent = m_player.GetPosition().Y;
	double ceilingPercent = 1.0 - floorPercent;
	int horizon = 0.5 * visionHeight;
	vector<double> depthBuffer(visionWidth,0.0);
	// Fill in the floor and ceiling
	for (int y = 0; y < visionHeight; y++) {
		Pixel& color = y < horizon ? m_floorColor : m_ceilingColor;
		for (int x = 0; x < visionWidth; x++) {
			m_backBuffer->Set(x, y, color);
		}
	}
	// Raycast each column
	for (int columnIndex = 0; columnIndex < visionWidth; columnIndex++) {
		
		Vector2 rayStart = nearStart + (nearEnd - nearStart) * ((float)columnIndex / (float)visionWidth);
		Vector2 ray = (rayStart - playerPos).Normalized();
		for (auto& wall : m_walls) {
			Vector2 wallNormal = wall.GetNormal();
			Bitmap& texture = GetTexture(wall.Texture);
			if ((wall.Start - playerPos).Dot(playerHeading) > 0.f || (wall.End - playerPos).Dot(playerHeading) > 0.f) {
				float wallT;
				float rayT;
				if (GetLineIntersection(rayStart, ray, wall.Start, wall.End - wall.Start, rayT, wallT)) {
					if (rayT > 0.f && wallT >= 0.f && wallT <= 1.f) {
						double depth = 1.f / rayT;
						if (depth > depthBuffer[columnIndex]) {
							depthBuffer[columnIndex] = depth;
							double distance = rayT + (rayStart - playerPos).Length();

							int columnHeight = visionWidth / distance;
							int projectionHeight = std::min(visionHeight, columnHeight);
							int projectionOffset = std::max(0, -(int)(horizon - floorPercent * columnHeight));
							for (int y = 0; y < projectionHeight; y++) {
								int projectionY = horizon - columnHeight * floorPercent + y + projectionOffset;
								if (projectionY >= 0 && projectionY < visionHeight) {
									int sourceX = std::fmod((float)(texture.GetWidth() - 1) * wallT * (wall.Length()), texture.GetWidth());
									int sourceY = ((float)(y + projectionOffset) / columnHeight) * (float)texture.GetHeight();
									Pixel sample = texture.Get(sourceX, sourceY);
									// Shade the sample based off the infleciton to the wall normal (e.g. shallower = darker)
									float value = 0.5 + 0.5 * std::abs(wallNormal.Dot(ray));
									sample *= value;

									m_backBuffer->Set(columnIndex, projectionY, sample);
								}
							}
						}
						
					}
				}
			}
		}
		// Sprites
		for (auto& sprite : m_sprites) {
			Vector2 spritePos = Vector2(sprite.Position.X, sprite.Position.Z);
			Bitmap& texture = GetTexture(sprite.Texture);
			double distance = (spritePos - playerPos).Length();
			float wallT;
			float rayT;
			
			if (GetLineIntersection(rayStart, ray, spritePos + playerHeading.Left() * 0.5f,playerHeading.Right(), rayT, wallT)) {
				if (rayT > 0.f && wallT >= 0.f && wallT <= 1.f) {
					double depth = 1.f / distance;
					if (depth > depthBuffer[columnIndex]) {

						int columnHeight = visionWidth / distance;
						int projectionHeight = std::min(visionHeight, columnHeight);
						int projectionOffset = std::max(0, -(int)(horizon - floorPercent * columnHeight));
						for (int y = 0; y < projectionHeight; y++) {
							int projectionY = horizon - columnHeight * floorPercent + y + projectionOffset;
							if (projectionY >= 0 && projectionY < visionHeight) {
								int sourceX = (float)(texture.GetWidth() - 1) * wallT;
								int sourceY = ((float)(y + projectionOffset) / columnHeight) * (float)texture.GetHeight();
								Pixel sample = texture.Get(sourceX, sourceY);

								m_backBuffer->Add(columnIndex, projectionY, sample);
							}
						}
					}
				}
			}
		}
	}
	
	glDrawPixels(m_backBuffer->GetWidth(), m_backBuffer->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_backBuffer->GetPixels());
}

void World::UpdateKeyState(char key, bool state)
{
	m_keyStates[key] = state;
}

void World::UpdateButtonState(int button, bool state)
{
	m_buttonStates[button] = state;
}

void World::UpdateMousePosition(Vector2 position)
{

	m_mouseDelta += position - m_lastMousePos;
	m_lastMousePos = position;
}

Bitmap& World::GetTexture(string name)
{
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return *(it->second);
	}
	else {
		// Load the texture from file
		auto texture = std::make_shared<Bitmap>(Bitmap::FromFile(name));
		m_textures.insert(std::make_pair(name, texture));
		return *texture;
	}
}

void World::UpdateBackBuffer(int width, int height)
{
	m_backBuffer.reset(new Bitmap(width, height));
}

bool World::GetLineIntersection(Vector2 startA, Vector2 dirA, Vector2 startB, Vector2 dirB, float& tA, float& tB)
{
	if (dirA.Dot(dirB.Right()) != 0.f) {
		tA = (dirB.X * (startA.Y - startB.Y) + dirB.Y * (startB.X - startA.X)) / (dirA.X * dirB.Y - dirA.Y * dirB.X);
		tB = (dirA.X * (startB.Y - startA.Y) + dirA.Y * (startA.X - startB.X)) / (dirB.X * dirA.Y - dirB.Y * dirA.X);
		return true;
	}
	return false;
}

void World::CreateWallPath(string texture, vector<Vector2> corners)
{
	for (int i = 0; i < corners.size() - 1; i++) {
		Vector2 & start = corners[i];
		Vector2 & end = corners[i + 1];
		m_walls.push_back(Wall(start, end, texture));
	}
}
