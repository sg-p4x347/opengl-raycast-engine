#include "pch.h"
#include "World.h"
#include "Utility.h"
#include "Item.h"
#include "Player.h"
#include "Door.h"
#include "AnimatedWall.h"
#include "Spider.h"
#include "RenderJob.h"

const float World::REGION_WIDTH = 16.f;
const float World::UPDATE_RANGE = 256.f;

World::World()
{

	// The player
	m_player = std::make_shared<Player>(Vector3(0.5f, 0.5f, -10.5f), 0.f, 1.f, 0.1f, 1000.f, 2.f, 0.25f);
	AddSprite(m_player);
	m_floorColor = Pixel(26, 26, 26, 255);
	m_ceilingColor = Pixel(40, 40, 40, 255);
	AddRooms();
}



void World::AddRooms()
{
	// DEFAULT ROOM 
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
			Vector2(2,0),
			Vector2(2,-7)
		}
	);
	CreateWallPath(
		"bricks.bmp",
		vector<Vector2> {
			Vector2(3,-7),
			Vector2(3,0),
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



	//CreateWallArc("bricks.bmp", Vector2(2.f, 2.f), 1.f, 0.f, M_PI * 2.f, M_PI * 2.f / 6.f);

	// DEVLYN'S ROOM

	// PAUL'S ROOM

	// ANTHONY'S ROOM

	// GAGE'S ROOM
	// Starting door
	AddWall(std::make_shared<Door>(Vector2(0, -10), Vector2(0, -11), "door.bmp", "key.bmp", Vector2(0.f, 0.25f), false));

	// Left door
	AddWall(std::make_shared<Door>(Vector2(2, -9), Vector2(3, -9.5), "door.bmp", "key.bmp", Vector2(0.f, 0.25f), false));
	// Right door
	//AddWall(std::make_shared<Door>(Vector2(2,-12), Vector2(3, -11.5), "door.bmp", "key.bmp", Vector2(0.f, 0.25f), false));

	CreateWallPath(
		"bricks.bmp", 
		vector<Vector2>{
			Vector2(0, -10),
			Vector2(1, -10),
			Vector2(2, -9),
			Vector2(2, -7),
			
		}
	);
	CreateWallPath(
		"bricks.bmp",
		vector<Vector2>{
		Vector2(3, -7),
			Vector2(3, -10),
			Vector2(5, -10),
			Vector2(5, -7),
			Vector2(14, -7)
	});
	CreateWallArc("bricks.bmp", Vector2(14, -10), 3.f, 0.f, M_PI / 2.f, M_PI / 8.f);
	CreateWallPath(
		"bricks_mossy.bmp",
		vector<Vector2>{
			Vector2(17,-10),
			Vector2(20, -10),
				Vector2(20, -16),
				Vector2(17, -16),
				Vector2(16, -17),
				Vector2(16.5, -17.5),
				Vector2(15.5, -18.5),
				Vector2(15,-18),
				Vector2(13,-20),
				Vector2(8,-20),
				Vector2(8,-18),
				Vector2(10,-16),
				Vector2(10, -15.5),
				Vector2(9.5, -15.5),
				Vector2(7,-18),
				Vector2(7,-20),
				Vector2(2,-20),
				Vector2(2,-12),
				Vector2(1, -11),
				Vector2(0,-11)
		}
	);
	CreateWallPath(
		"bricks.bmp",
		vector<Vector2>{
			Vector2(3,-11),
			Vector2(5,-11),
			Vector2(5,-14),
			Vector2(14,-14)
		}
	);
	CreateWallArc("bricks.bmp", Vector2(14, -11), 3.f, 3.f * M_PI / 2.f, M_PI * 2.f, M_PI / 8.f);

	CreateWallPath(
		"bricks.bmp",
		vector<Vector2>{
			Vector2(17,-11),
				Vector2(18,-11),
				Vector2(18,-15),
				Vector2(17,-15),
				Vector2(16,-16),
				Vector2(15.5,-15.5),
				Vector2(14.5,-16.5),
				Vector2(15,-17),
				Vector2(14,-18),
				Vector2(14,-14.5),
				Vector2(5, -14.5),
				Vector2(5,-19),
				Vector2(3,-19),
				Vector2(3,-11)
		}
	);
	// Knife
	
	AddSprite(std::make_shared<Item>(Vector3(4.5,0.f,-10.5), 0.25f, "knife.bmp"));
	
	// Room 1 spiders
	AddSprite(std::make_shared<Spider>(Vector3(10, 0.f, -9)));
	AddSprite(std::make_shared<Spider>(Vector3(10, 0.f, -12)));
	AddSprite(std::make_shared<Spider>(Vector3(16, 0.f, -10)));

	// Room 2 spiders
	AddSprite(std::make_shared<Spider>(Vector3(19, 0.f, -13)));
	// Key
	AddSprite(std::make_shared<Item>(Vector3(15.f, 0.f, -16.5), 0.25f, "key.bmp"));
	// Shotgun
	AddSprite(std::make_shared<Item>(Vector3(15.5, 0.f, -18), 0.25f, "shotgun.bmp"));
	// Room 3 spiders
	AddSprite(std::make_shared<Spider>(Vector3(10, 0.f, -17)));
	AddSprite(std::make_shared<Spider>(Vector3(12, 0.f, -17)));
	AddSprite(std::make_shared<Spider>(Vector3(11, 0.f, -19)));
	AddSprite(std::make_shared<Spider>(Vector3(10, 0.f, -19)));
	// Room 4 spiders
	AddSprite(std::make_shared<Spider>(Vector3(7, 0.f, -15)));
	AddSprite(std::make_shared<Spider>(Vector3(6, 0.f, -16)));
}

void World::OpenMenu(Menu menu)
{
	m_menu = menu;
}

void World::Update(double& elapsed)
{
	// Abort
	if (m_keyStates[27]) {
		UnlockPointer();
	}
	if (m_menu == Menu::HUD) {
		Vector2 playerPos = m_player->GetMapPosition();
		m_loadedRegions.clear();
		RegionsContainingRect(Rect(playerPos - Vector2(UPDATE_RANGE, UPDATE_RANGE), Vector2(2.f * UPDATE_RANGE, 2.f * UPDATE_RANGE)), m_loadedRegions);
		m_sprites = CollectSprites(m_loadedRegions);
		UpdateSprites(elapsed, m_sprites);
		m_walls = CollectWalls(m_loadedRegions);
		UpdateWalls(elapsed, m_walls);
		if (m_player->Health <= 0.f) {
			OpenMenu(World::Menu::Death);
		}
	}
	else if (m_keyStates[13]) {
		switch (m_menu) {
		case Menu::Death:
			ResetPlayer();
			break;
		}
		m_menu = Menu::HUD;
	}
}

void World::Render()
{
	RenderPerspective();
	RenderHUD();
	RenderMenu();
}

void World::UpdateKeyState(char key, bool state)
{
	m_keyStates[key] = state;
}

void World::UpdateButtonState(int button, bool state)
{
	m_buttonStates[button] = state;
	LockPointer();
}

void World::UpdateMousePosition(Vector2 position)
{
	if (m_lockPointer) {
		Vector2 center(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		m_mouseDelta += position - center;
		glutWarpPointer(center.X, center.Y);
	}
	else {
		m_mousePosition = position;
	}

	
}

Vector2 World::GetMouseDelta()
{
	return m_mouseDelta;
}

void World::ResetMouseDelta()
{
	m_mouseDelta = Vector2(0, 0);
}

Bitmap& World::GetTexture(string name)
{
	auto it = m_textures.find(name);
	if (it != m_textures.end()) {
		return *(it->second);
	}
	else {
		// Load the texture from file
		auto texture = std::make_shared<Bitmap>(Bitmap::FromFile("images/" + name));
		m_textures.insert(std::make_pair(name, texture));
		return *texture;
	}
}

void World::UpdateBackBuffer(int width, int height)
{
	m_backBuffer.reset(new Bitmap(width, height));
	// specify a viewing area
	glViewport(0, 0, width, height);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
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

void World::CreateWallArc(string texture, Vector2 center,float radius, float startAngle, float endAngle, float angleStep)
{
	vector<Vector2> path;
	for (float angle = startAngle; angle <= endAngle + 0.001f; angle += angleStep) { // Fudge factor for floating point inaccuracy
		path.push_back(center + Vector2(std::cosf(angle), std::sinf(angle)) * radius);
	}
	CreateWallPath(texture, path);
}

void World::LockPointer()
{
	m_lockPointer = true;
	glutSetCursor(GLUT_CURSOR_NONE);
}

void World::UnlockPointer()
{
	m_lockPointer = false;
	glutSetCursor(GLUT_CURSOR_INHERIT);
}

void World::RenderPerspective()
{
	std::lock_guard<mutex> lock(m_mutex);
	Vector2 playerPos = m_player->GetMapPosition();
	Vector2 playerHeading = m_player->GetHeading();
	Vector2 nearStart = playerPos + playerHeading.Left() * std::tan(m_player->FOV * 0.5f) * m_player->NearPlane + playerHeading * m_player->NearPlane;
	Vector2 farStart = playerPos + playerHeading.Left() * std::tan(m_player->FOV * 0.5f) * m_player->FarPlane + playerHeading * m_player->FarPlane;
	Vector2 nearEnd = playerPos + playerHeading.Right() * std::tan(m_player->FOV * 0.5f) * m_player->NearPlane + playerHeading * m_player->NearPlane;
	Vector2 farEnd = playerPos + playerHeading.Right() * std::tan(m_player->FOV * 0.5f) * m_player->FarPlane + playerHeading * m_player->FarPlane;
	Vector2 leftFrustumNormal = (farStart - nearStart).Right().Normalized();
	Vector2 rightFrustumNormal = (farEnd - nearEnd).Left().Normalized();
	static const int pixelSize = 4;
	int visionWidth = m_backBuffer->GetWidth() / pixelSize;
	int visionHeight = m_backBuffer->GetHeight() / pixelSize;
	double floorPercent = m_player->Position.Y;
	double ceilingPercent = 1.0 - floorPercent;
	int horizon = 0.5 * visionHeight;
	vector<double> depthBuffer(visionWidth, 0.0);
	// Fill in the floor and ceiling
	for (int y = 0; y < visionHeight; y++) {
		Pixel& color = y < horizon ? m_floorColor : m_ceilingColor;
		for (int x = 0; x < visionWidth; x++) {
			m_backBuffer->Set(x, y, color);
		}
	}
	set<shared_ptr<Region>> regions;
	RegionsContainingRect(Rect::BoundingRect(playerPos, farStart, farEnd), regions);
	set<shared_ptr<Wall>> walls = CollectWalls(regions);
	vector<RenderJob> renderJobs;
	for (auto& wall : walls) {
		Vector2 playerToStart = wall->Start - playerPos;
		Vector2 playerToEnd = wall->End - playerPos;
		if (playerToStart.Dot(playerHeading) > 0.f
			|| playerToEnd.Dot(playerHeading) > 0.f) {
			renderJobs.push_back(RenderJob(
				wall->Texture, 
				wall->Start,
				wall->End,
				wall->Alpha,
				wall->TextureSampleOffset, 
				wall->WrapTextureX, 
				wall->WrapTextureY
			));
		}
	}

	for (auto& sprite : m_sprites) {
		if (sprite->Texture != "") {
			Vector2 spritePos = Vector2(sprite->Position.X, sprite->Position.Z);
			Vector2 start = spritePos + playerHeading.Left() * 0.5f;
			Vector2 end = spritePos + playerHeading.Right() * 0.5f;
			Vector2 playerToStart = start - playerPos;
			Vector2 playerToEnd = end - playerPos;
			if (playerToStart.Dot(playerHeading) > 0.f
				|| playerToEnd.Dot(playerHeading) > 0.f) {
				renderJobs.push_back(RenderJob(
					sprite->Texture,
					start,
					end,
					true,
					Vector2(),
					false,
					false
				));
			}
		}
	}
	
	//std::sort(renderJobs.begin(), renderJobs.end(), [=](const RenderJob& a, const RenderJob& b) {
	//	if (!a.Alpha) {
	//		if (b.Alpha) {
	//			return true; // Always render opaque walls before alpha walls
	//		}
	//		else {
	//			// Render nearer opaque walls first
	//			return ((a.Start + a.End) * 0.5f - playerPos).LengthSquared() < ((b.Start + b.End) * 0.5f - playerPos).LengthSquared();
	//		}
	//	}
	//	else {
	//		if (!b.Alpha) {
	//			return false; // Always render alpha walls after opaque walls
	//		}
	//		else {
	//			// Render further alpha walls first
	//			return ((a.Start + a.End) * 0.5f - playerPos).LengthSquared() > ((b.Start + b.End) * 0.5f - playerPos).LengthSquared();
	//		}
	//	}
	//});

	
	// Raycast each column
	for (int columnIndex = 0; columnIndex < visionWidth; columnIndex++) {
		
		Vector2 rayStart = nearStart + (nearEnd - nearStart) * ((float)columnIndex / (float)visionWidth);
		Vector2 ray = (rayStart - playerPos).Normalized();
		for (auto& job : renderJobs) {
			Bitmap& texture = GetTexture(job.Texture);
			float wallT;
			float rayT;
			if (GetLineIntersection(rayStart, ray, job.Start, job.End - job.Start, rayT, wallT)) {
				if (rayT > 0.f && wallT >= 0.f && wallT <= 1.f) {
					double depth = 1.f / rayT;
					job.Depth = depth;
					if (depth > depthBuffer[columnIndex]) {
						// Only opaque jobs write to the depth buffer
						if (!job.Alpha) {
							depthBuffer[columnIndex] = depth;
						}
						double distance = rayT + (rayStart - playerPos).Length();

						int columnHeight = visionWidth / distance;
						int projectionHeight = std::min(visionHeight, columnHeight);
						int projectionOffset = std::max(0, -(int)(horizon - floorPercent * columnHeight));
						for (int y = 0; y < projectionHeight; y++) {
							int projectionY = horizon - columnHeight * floorPercent + y + projectionOffset;
							if (projectionY >= 0 && projectionY < visionHeight) {
								int sourceX = (wallT * job.Length + job.TextureSampleOffset.X) * (float)(texture.GetWidth() - 1);
								int sourceY = ((float)(y + projectionOffset) / columnHeight + job.TextureSampleOffset.Y) * (float)(texture.GetHeight() - 1);
								if (job.WrapTextureX)
									sourceX = (sourceX + texture.GetWidth()) % (texture.GetWidth() - 1);
								if (job.WrapTextureY)
									sourceY = (sourceY + texture.GetHeight()) % (texture.GetHeight() - 1);

								Pixel sample = texture.Get(sourceX, sourceY);
								// Shade the sample based off the infleciton to the wall normal (e.g. shallower = darker)
								float value = 0.5 + 0.5 * std::abs(job.Normal.Dot(ray));
								sample *= value;

								m_backBuffer->Add(columnIndex, projectionY, sample);
							}
						}
					}
				}
			}
		}
		std::sort(renderJobs.begin(), renderJobs.end(), [=](const RenderJob& a, const RenderJob& b) {
			if (!a.Alpha) {
				if (b.Alpha) {
					return true; // Always render opaque walls before alpha walls
				}
				else {
					// Render nearer opaque walls first
					return a.Depth > b.Depth;
				}
			}
			else {
				if (!b.Alpha) {
					return false; // Always render alpha walls after opaque walls
				}
				else {
					// Render further alpha walls first
					return a.Depth < b.Depth;
				}
			}
			});
	}


	glRasterPos2d(0, 0);
	glPixelZoom(pixelSize, pixelSize);
	glDrawPixels(m_backBuffer->GetWidth(), m_backBuffer->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)m_backBuffer->GetPixels());
}

void World::RenderHUD()
{
	m_player->hud.render(m_backBuffer->GetWidth(), m_backBuffer->GetHeight());
}

void World::RenderMenu()
{
	switch (m_menu) {
	case Menu::Death:
	{
		//***************************************************************************************
		int skullWidth = 30;
		int skullHeight = 30;
		GLubyte skull[] = {
			0x00, 0x00, 0x00, 0x00,
			0x0e, 0x00, 0x01, 0xc0,
			0x1f, 0x00, 0x03, 0xc0,
			0x1f, 0x0f, 0xc7, 0xe0,
			0x7f, 0x9f, 0xe7, 0xf8,			//5
			0x7f, 0x9f, 0xe7, 0xf8,
			0x7f, 0xff, 0xff, 0xf8,
			0x3f, 0xff, 0xff, 0xf0,
			0x03, 0xf8, 0x3f, 0x00,
			0x03, 0xf8, 0x7f, 0x00,			//10
			0x03, 0xf8, 0x7f, 0x00,
			0x03, 0x07, 0x83, 0x00,
			0x03, 0x03, 0x03, 0x00,
			0x07, 0x03, 0x03, 0x00,
			0x07, 0x03, 0x03, 0x00,			//15
			0x0f, 0x03, 0x03, 0x00,
			0x0f, 0x03, 0x03, 0x00,
			0x0f, 0xff, 0xff, 0xc0,
			0x0f, 0xff, 0xff, 0xc0,
			0x0f, 0xff, 0xff, 0xc0,			//20
			0x0f, 0xff, 0xff, 0x80,
			0x07, 0xff, 0xff, 0x80,
			0x3f, 0xff, 0xff, 0xf0,
			0x7f, 0xff, 0xff, 0xf8,
			0x7f, 0xff, 0xff, 0xf8,			//25
			0x7f, 0xff, 0xff, 0xf0,
			0x3f, 0x0f, 0xc7, 0xf0,
			0x0f, 0x00, 0x03, 0xc0,
			0x0f, 0x00, 0x01, 0xc0,
			0x00, 0x00, 0x00, 0x00			//30

		};

		//**************************************************************************************
		
		glBegin(GL_POLYGON);
		glColor3f(1.f, 0.f, 0.f);
		glVertex2i(0, 0);
		glVertex2i(0, m_backBuffer->GetHeight());
		glVertex2i(m_backBuffer->GetWidth(), m_backBuffer->GetHeight());
		glVertex2i(m_backBuffer->GetWidth(), 0);
		glEnd();

		glColor3f(0, 0, 0);
		
		int centerX = m_backBuffer->GetWidth() / 2;
		int centerY = m_backBuffer->GetHeight() / 2;

		glRasterPos2d(centerX - skullWidth / 2, centerY - skullHeight / 2);
		glBitmap(skullWidth, skullHeight, 0, 0, 0, 0, skull);
		string message = "YOU DIED!";
		glRasterPos2f(m_backBuffer->GetWidth() / 2 - MeasureString(GLUT_BITMAP_TIMES_ROMAN_24,message) / 2, m_backBuffer->GetHeight() / 2 + skullHeight);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, message);
	}
		break;
	case Menu::Credits:
	{
		glBegin(GL_POLYGON);
		glColor3f(0.f, 0.f, 0.f);
		glVertex2i(0, 0);
		glVertex2i(0, m_backBuffer->GetHeight());
		glVertex2i(m_backBuffer->GetWidth(), m_backBuffer->GetHeight());
		glVertex2i(m_backBuffer->GetWidth(), 0);
		glEnd();


		int centerX = m_backBuffer->GetWidth() / 2;
		int centerY = m_backBuffer->GetHeight() / 2;
		glColor3f(1.f, 1.f, 1.f);
		string made_by = "Made by:";
		glRasterPos2f(centerX, centerY + 96);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, made_by);
		string anthony = "Anthony Harris";
		glRasterPos2f(centerX, centerY + 72);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, anthony);
		string paul = "Paul Durham";
		glRasterPos2f(centerX, centerY + 48);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, paul);
		string devlyn = "Devlyn Hogue III";
		glRasterPos2f(centerX, centerY + 24);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, devlyn);
		string gage = "Gage Coates";
		glRasterPos2f(centerX, centerY);
		DrawString(GLUT_BITMAP_TIMES_ROMAN_24, gage);
	}
		break;
	}
}

int World::MeasureString(void* font, string text)
{
	int width = 0;
	for (auto& ch : text) {
		width += glutBitmapWidth(font, ch);
	}
	return width;
}

void World::DrawString(void* font, string text)
{
	for (auto& ch : text) {
		glutBitmapCharacter(font, ch);
	}
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

void World::ResetPlayer()
{
	if (m_player)
		RemoveSprite(m_player);

	m_player->Health = Player::MaxHealth;
	AddSprite(m_player);
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
