#include "pch.h"
#include "World.h"
#include "Utility.h"
#include "Item.h"
#include "Player.h"
#include "Door.h"
#include "AnimatedWall.h"
#include "Spider.h"
const float World::MOUSE_GAIN = 0.1f;
const float World::REGION_WIDTH = 16.f;
const float World::UPDATE_RANGE = 256.f;

World::World()
{

	// The player
	m_player = std::make_shared<Player>(Vector3(2.f, 0.5f, 2.f), 0.f, 1.f, 0.1f, 1000.f, 4.f, 0.25f);
	AddSprite(m_player);
	m_floorColor = Pixel(26, 26, 26, 255);
	m_ceilingColor = Pixel(40, 40, 40, 255);
	// The key
	AddSprite(std::make_shared<Item>(Vector3(19.f, 0.f, 1.f), 0.25f, "key.bmp"));
	// The spiders
	AddSprite(std::make_shared<Spider>(Vector3(14, 0.f, 8)));
	AddSprite(std::make_shared<Spider>(Vector3(15, 0.f, 7)));
	AddSprite(std::make_shared<Spider>(Vector3(17, 0.f, 2)));
	CreateWallPath(
		"bricks.bmp",
		vector<Vector2> {
			Vector2(9, 8),
			Vector2(6, 4),
			Vector2(0, 4),
			Vector2(0, 0),
			Vector2(20, 0),
			Vector2(20, 5),
			Vector2(18, 7),
			Vector2(18, 13),
			Vector2(13, 13),
			Vector2(10, 9)
		}
	);
	// Columns
	for (int x = 8; x < 20; x += 2) {
		CreateWallRect(
			"bricks_weathered.bmp",
			Rect(x, 4, 0.25f, 0.25f)
		);
	}
	// Hallway
	CreateWallPath(
		"bricks_mossy.bmp",
		vector<Vector2> {
		Vector2(9, 8),
			Vector2(0, 8)
	}
	);
	CreateWallPath(
		"bricks_mossy.bmp",
		vector<Vector2> {
		Vector2(0, 9),
			Vector2(10, 9)
		}
	);
	// Waterfall
	auto waterWall = std::make_shared<AnimatedWall>(Vector2(8.75, 8), Vector2(9.75, 9), "water.bmp", Vector2(0.f, -2.f));
	waterWall->Collision = false;
	waterWall->Alpha = true;
	AddWall(waterWall);

	// Door
	AddWall(std::make_shared<Door>(Vector2(4, 8), Vector2(4, 9), "door.bmp", "key.bmp", Vector2(0.f, 0.25f), false));

	// Omega Gaming Project logo
	AddWall(std::make_shared<Wall>(Vector2(0, 8), Vector2(0, 9), "logo.bmp"));
}

void World::Update(double& elapsed)
{
	Vector2 playerPos = m_player->GetMapPosition();
	m_loadedRegions.clear();
	RegionsContainingRect(Rect(playerPos - Vector2(UPDATE_RANGE, UPDATE_RANGE), Vector2(2.f * UPDATE_RANGE, 2.f * UPDATE_RANGE)), m_loadedRegions);
	m_sprites = CollectSprites(m_loadedRegions);
	UpdateSprites(elapsed, m_sprites);
	m_walls = CollectWalls(m_loadedRegions);
	UpdateWalls(elapsed, m_walls);
}

void World::Render()
{
	std::lock_guard<mutex> lock(m_mutex);
	Vector2 playerPos = m_player->GetMapPosition();
	Vector2 playerHeading = m_player->GetHeading();
	Vector2 nearStart = playerPos + playerHeading.Left() * std::tan(m_player->FOV * 0.5f) * m_player->NearPlane + playerHeading * m_player->NearPlane;
	Vector2 farStart = playerPos + playerHeading.Left() * std::tan(m_player->FOV * 0.5f) * m_player->FarPlane + playerHeading * m_player->FarPlane;
	Vector2 nearEnd = playerPos + playerHeading.Right() * std::tan(m_player->FOV * 0.5f) * m_player->NearPlane + playerHeading * m_player->NearPlane;
	Vector2 farEnd = playerPos + playerHeading.Right() * std::tan(m_player->FOV * 0.5f) * m_player->FarPlane + playerHeading * m_player->FarPlane;
	static const int pixelSize = 2;
	int visionWidth = m_backBuffer->GetWidth() / pixelSize;
	int visionHeight = m_backBuffer->GetHeight() / pixelSize;
	double floorPercent = m_player->Position.Y;
	double ceilingPercent = 1.0 - floorPercent;
	int horizon = 0.5 * visionHeight;
	vector<double> depthBuffer(visionWidth,0.0);
	// Fill in the floor and ceiling
	for (int y = 0; y < visionHeight; y++) {
		Pixel& color = y < horizon ? m_floorColor : m_ceilingColor;
		for (int x = 0; x < visionWidth; x++) {
			m_backBuffer->Set(x * pixelSize, y * pixelSize, pixelSize, pixelSize, color);
		}
	}
	set<shared_ptr<Region>> regions;
	RegionsContainingRect(Rect::BoundingRect(playerPos, farStart, farEnd), regions);
	set<shared_ptr<Wall>> walls = CollectWalls(regions);
	vector<shared_ptr<Wall>> depthSortedWalls;
	for (auto& wall : walls)
		depthSortedWalls.push_back(wall);
	
	std::sort(depthSortedWalls.begin(), depthSortedWalls.end(), [=](const shared_ptr<Wall>& a, const shared_ptr<Wall>& b) {
		if (!a->Alpha) {
			if (b->Alpha) {
				return true; // Always render opaque walls before alpha walls
			}
			else {
				// Render nearer opaque walls first
				return ((a->Start + a->End) * 0.5f - playerPos).LengthSquared() < ((b->Start + b->End) * 0.5f - playerPos).LengthSquared();
			}
		}
		else {
			if (!b->Alpha) {
				return false; // Always render alpha walls after opaque walls
			}
			else {
				// Render further alpha walls first
				return ((a->Start + a->End) * 0.5f - playerPos).LengthSquared() > ((b->Start + b->End) * 0.5f - playerPos).LengthSquared();
			}
		}
	});
	// Raycast each column
	for (int columnIndex = 0; columnIndex < visionWidth; columnIndex++) {
		
		Vector2 rayStart = nearStart + (nearEnd - nearStart) * ((float)columnIndex / (float)visionWidth);
		Vector2 ray = (rayStart - playerPos).Normalized();
		// Walls
		for (auto& wall : depthSortedWalls) {
			Vector2 wallNormal = wall->GetNormal();
			Bitmap& texture = GetTexture(wall->Texture);
			if ((wall->Start - playerPos).Dot(playerHeading) > 0.f || (wall->End - playerPos).Dot(playerHeading) > 0.f) {
				float wallT;
				float rayT;
				if (GetLineIntersection(rayStart, ray, wall->Start, wall->End - wall->Start, rayT, wallT)) {
					if (rayT > 0.f && wallT >= 0.f && wallT <= 1.f) {
						double depth = 1.f / rayT;
						if (depth > depthBuffer[columnIndex]) {
							if (!wall->Alpha) {
								depthBuffer[columnIndex] = depth;
							}
							double distance = rayT + (rayStart - playerPos).Length();

							int columnHeight = visionWidth / distance;
							int projectionHeight = std::min(visionHeight, columnHeight);
							int projectionOffset = std::max(0, -(int)(horizon - floorPercent * columnHeight));
							for (int y = 0; y < projectionHeight; y++) {
								int projectionY = horizon - columnHeight * floorPercent + y + projectionOffset;
								if (projectionY >= 0 && projectionY < visionHeight) {
									int sourceX = (wallT * (wall->Length()) + wall->TextureSampleOffset.X) * (float)(texture.GetWidth() - 1);
									int sourceY = ((float)(y + projectionOffset) / columnHeight + wall->TextureSampleOffset.Y) * (float)(texture.GetHeight() - 1);
									if (wall->WrapTextureX)
										sourceX = (sourceX + texture.GetWidth()) % (texture.GetWidth() - 1);
									if (wall->WrapTextureY)
										sourceY = (sourceY + texture.GetHeight()) % (texture.GetHeight() - 1);

									Pixel sample = texture.Get(sourceX, sourceY);
									// Shade the sample based off the infleciton to the wall normal (e.g. shallower = darker)
									float value = 0.5 + 0.5 * std::abs(wallNormal.Dot(ray));
									sample *= value;

									m_backBuffer->Add(columnIndex * pixelSize, projectionY * pixelSize, pixelSize, pixelSize, sample);
								}
							}
						}
					}
				}
			}
		}
		vector<shared_ptr<Sprite>> depthSortedSprites;
		for (auto& sprite : m_sprites) {
			if (sprite->Texture != "") {
				Vector2 spritePos = Vector2(sprite->Position.X, sprite->Position.Z);
				Vector2 toSprite = spritePos - playerPos;
				if (toSprite.Dot(playerHeading) >= 0.f) {
					depthSortedSprites.push_back(sprite);
				}
			}
		}
		std::sort(depthSortedSprites.begin(), depthSortedSprites.end(), [=](const shared_ptr<Sprite> & a, const shared_ptr<Sprite> & b) -> bool {
			Vector2 aPos = Vector2(a->Position.X, a->Position.Z);
			Vector2 bPos = Vector2(b->Position.X, b->Position.Z);
			return (aPos - playerPos).LengthSquared() > (bPos - playerPos).LengthSquared();
		});
		// Sprites
		for (auto& sprite : depthSortedSprites) {
			if (sprite->Texture != "") {
				Vector2 spritePos = Vector2(sprite->Position.X, sprite->Position.Z);
				Vector2 toSprite = spritePos - playerPos;
				if (toSprite.Dot(playerHeading) >= 0.f) {
					Bitmap& texture = GetTexture(sprite->Texture);
					double distance = toSprite.Length();
					float wallT;
					float rayT;

					if (GetLineIntersection(rayStart, ray, spritePos + playerHeading.Left() * 0.5f, playerHeading.Right(), rayT, wallT)) {
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
										int sourceY = ((float)(y + projectionOffset) / columnHeight) * (float)(texture.GetHeight() - 1);
										Pixel sample = texture.Get(sourceX, sourceY);

										m_backBuffer->Add(columnIndex * pixelSize, projectionY * pixelSize, pixelSize, pixelSize, sample);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	glDrawPixels(m_backBuffer->GetWidth(), m_backBuffer->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_backBuffer->GetPixels());
	
	// HUD
	int inventoryIndex = 0;
	for (auto& entry : m_player->Inventory) {
		if (entry.second > 0) {
			auto& texture = GetTexture(entry.first);
			glDrawPixels(texture.GetWidth(), texture.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture.GetPixels());
			inventoryIndex++;
		}
	}
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

set<shared_ptr<Sprite>> World::GetSpritesInRange(Vector2 center, float range)
{
	
	set<shared_ptr<Sprite>> results;
	for (auto& sprite : m_sprites) {
		const float rangeSquared = (range + sprite->Radius) * (range + sprite->Radius);
		if ((sprite->GetMapPosition() - center).LengthSquared() <= rangeSquared) {
			results.insert(sprite);
		}
	}
	return results;
}

set<shared_ptr<Wall>> World::GetWallsInRange(Vector2 center, float range)
{
	
	set<shared_ptr<Region>> regions;
	RegionsContainingRect(Rect(center - Vector2(range, range), Vector2(2.f * range, 2.f * range)), regions);
	return CollectWalls(regions);
}

void World::AddWall(shared_ptr<Wall> wall)
{
	// Add to every region that this wall intersects
	set<shared_ptr<Region>> regions;
	RegionsContainingSegment(wall->Start, wall->End, regions);
	for (auto& region : regions) {
		region->Walls.insert(wall);
	}
}

shared_ptr<Player> World::GetPlayer()
{
	return m_player;
}

void World::CreateWallPath(string texture, vector<Vector2> corners)
{
	Bitmap& bitmap = GetTexture(texture);
	bool hasAlpha = false;
	for (size_t x = 0; x < bitmap.GetWidth(); x++) {
		for (size_t y = 0; y < bitmap.GetHeight(); y++) {
			if (bitmap.Get(x, y).A < 255) {
				hasAlpha = true;
				goto alphaCheckDone;
			}
		}
	}
	alphaCheckDone:
	for (int i = 0; i < corners.size() - 1; i++) {
		Vector2 & start = corners[i];
		Vector2 & end = corners[i + 1];
		auto wall = std::make_shared<Wall>(start, end, texture);
		wall->Alpha = hasAlpha;
		AddWall(wall);
	}
}

void World::CreateWallRect(string texture, Rect rect)
{
	vector<Vector2> corners{
		rect.Position,
		rect.Position + Vector2(rect.Size.X, 0.f),
		rect.Position + rect.Size,
		rect.Position + Vector2(0.f, rect.Size.Y),
		rect.Position
	};
	CreateWallPath(texture, corners);
}

void World::UpdateSprites(double& elapsed, set<shared_ptr<Sprite>> & sprites)
{
	for (auto& sprite : sprites) {
		sprite->Update(elapsed, this);
	}
}

void World::UpdateWalls(double& elapsed, set<shared_ptr<Wall>>& walls)
{
	for (auto& wall : walls) {
		wall->Update(elapsed, this);
	}
}

void World::RegionsContainingPoint(Vector2 point, set<shared_ptr<Region>>& regions)
{
	int regionX = std::floor(point.X / REGION_WIDTH);
	int regionY = std::floor(point.Y / REGION_WIDTH);
	shared_ptr<Region> region;
	if (!TryGetRegion(regionX, regionY, region)) {
		region = AddNewRegion(regionX, regionY);
	}
	regions.insert(region);
	bool xBoundary = point.X == regionX * REGION_WIDTH;
	bool yBoundary = point.Y == regionY * REGION_WIDTH;
	if (xBoundary) {
		shared_ptr<Region> region;
		if (!TryGetRegion(regionX - 1, regionY, region)) {
			region = AddNewRegion(regionX - 1, regionY);
		}
	}
	if (yBoundary) {
		shared_ptr<Region> region;
		if (!TryGetRegion(regionX, regionY - 1, region)) {
			region = AddNewRegion(regionX, regionY - 1);
		}
	}
	if (xBoundary && yBoundary) {
		shared_ptr<Region> region;
		if (!TryGetRegion(regionX - 1, regionY - 1, region)) {
			region = AddNewRegion(regionX - 1, regionY - 1);
		}
	}
}

void World::RegionsContainingSegment(Vector2 start, Vector2 end, set<shared_ptr<Region>>& regions)
{
	RegionsContainingPoint(start, regions);
	RegionsContainingPoint(end, regions);

	Vector2 dir = (end - start).Normalized();
	int startRegionX = std::floor(start.X / REGION_WIDTH);
	int startRegionY = std::floor(start.Y / REGION_WIDTH);
	int endRegionX = std::floor(end.X / REGION_WIDTH);
	int endRegionY = std::floor(end.Y / REGION_WIDTH);

	if (dir.X != 0) {
		for (int regionX = startRegionX + 1; regionX <= endRegionX; regionX++) {
			float x = regionX * REGION_WIDTH;
			Vector2 point(x, start.Y + (dir.Y / dir.X) * (x - start.X));
			RegionsContainingPoint(point, regions);
		}
	}
	if (dir.Y != 0) {
		for (int regionY = startRegionY + 1; regionY <= endRegionY; regionY++) {
			float y = regionY * REGION_WIDTH;
			Vector2 point(start.X + (dir.X / dir.Y) * (y - start.Y), y);
			RegionsContainingPoint(point, regions);
		}
	}
}

 void World::RegionsContainingRect(Rect rect, set<shared_ptr<Region>>& regions)
{
	for (int x = std::floor(rect.Position.X / REGION_WIDTH); x <= std::floor((rect.Position.X + rect.Size.X) / REGION_WIDTH); x++) {
		for (int y = std::floor(rect.Position.Y / REGION_WIDTH); y <= std::floor((rect.Position.Y + rect.Size.Y) / REGION_WIDTH); y++) {
			shared_ptr<Region> region;
			if (TryGetRegion(x, y, region))
				regions.insert(region);
			
		}
	}
}

shared_ptr<Region> World::AddNewRegion(int x, int y)
{
	shared_ptr<Region> region = std::make_shared<Region>();
	m_regions[x][y] = region;
	return region;
}

bool World::TryGetRegion(int x, int y, shared_ptr<Region>& region)
{
	auto xIt = m_regions.find(x);
	if (xIt != m_regions.end()) {
		auto yIt = xIt->second.find(y);
		if (yIt != xIt->second.end()) {
			region = yIt->second;
			return true;
		}
	}
	return false;
}

set<shared_ptr<Wall>> World::CollectWalls(set<shared_ptr<Region>>& regions)
{
	set<shared_ptr<Wall>> walls;
	for (auto& region : regions) {
		walls.insert(region->Walls.begin(), region->Walls.end());
	}
	return walls;
}

set<shared_ptr<Sprite>> World::CollectSprites(set<shared_ptr<Region>>& regions)
{
	set<shared_ptr<Sprite>> sprites;
	for (auto& region : regions) {
		sprites.insert(region->Sprites.begin(), region->Sprites.end());
	}
	return sprites;
}
void World::RemoveSprite(Sprite* sprite)
{
	for (auto & existingSprite : m_sprites) {
		if (&*existingSprite == sprite) {
			RemoveSprite(existingSprite);
			break;
		}
	}
}

void World::AddSprite(shared_ptr<Sprite> sprite)
{
	set<shared_ptr<Region>> regions;
	RegionsContainingPoint(sprite->GetMapPosition(), regions);
	for (auto& region : regions) {
		region->Sprites.insert(sprite);
	}
}

void World::RemoveSprite(shared_ptr<Sprite> sprite)
{
	for (auto& region : m_loadedRegions) {
		region->Sprites.erase(sprite);
	}
}
