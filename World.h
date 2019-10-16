#pragma once
#include "pch.h"
#include "Wall.h"
#include "Player.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Region.h"
#include "Rect.h"
class World
{
public:
	enum class Menu {
		HUD,
		Death,
		Credits
	};
	friend class Sprite;
	friend class Player;
	friend class Item;
	World();
	void Update(double& elapsed);
	void Render();
	void UpdateKeyState(char key, bool state);
	void UpdateButtonState(int button, bool state);
	void UpdateMousePosition(Vector2 position);
	Vector2 GetMouseDelta();
	void ResetMouseDelta();
	Bitmap& GetTexture(string name);
	void UpdateBackBuffer(int width, int height);

	void AddRooms();
	void OpenMenu(Menu menu);
	
	shared_ptr<Player> GetPlayer();
	// Sprites
	set<shared_ptr<Sprite>> GetSpritesInRange(Vector2 center, float range);
	void RemoveSprite(Sprite* sprite);
	void AddSprite(shared_ptr<Sprite> sprite);
	void RemoveSprite(shared_ptr<Sprite> sprite);
	// Walls
	set<shared_ptr<Wall>> GetWallsInRange(Vector2 center, float range);
	void AddWall(shared_ptr<Wall> wall);
	void CreateWallPath(string texture, vector<Vector2> corners);
	void CreateWallRect(string texture, Rect rect);
	void CreateWallArc(string texture, Vector2 center, float radius, float startAngle, float endAngle, float angleStep = M_PI / 8);

private:
	static const float REGION_WIDTH;
	static const float UPDATE_RANGE;
	map<int, map<int, shared_ptr<Region>>> m_regions;

	set<shared_ptr<Region>> m_loadedRegions;
	shared_ptr<Player> m_player;
	set<shared_ptr<Wall>> m_walls;
	set<shared_ptr<Sprite>> m_sprites;
	mutex m_mutex;
	
	map<string, shared_ptr<Bitmap>> m_textures;
	Pixel m_floorColor;
	Pixel m_ceilingColor;
	unique_ptr<Bitmap> m_backBuffer;

	map<char, bool> m_keyStates;
	map<int, bool> m_buttonStates;
	Vector2 m_mouseDelta;
	Vector2 m_mousePosition;
	bool m_lockPointer;

	Menu m_menu;

private:
	//----------------------------------------------------------------
	// Cursor
	void LockPointer();
	void UnlockPointer();

	//----------------------------------------------------------------
	// Rendering
	void RenderPerspective();
	void RenderHUD();
	void RenderMenu();
	int MeasureString(void*font, string text);
	void DrawString(void* font, string text);
	//----------------------------------------------------------------
	// Updating
	void UpdateSprites(double& elapsed, set<shared_ptr<Sprite>>& sprites);
	void UpdateWalls(double& elapsed, set<shared_ptr<Wall>>& walls);
	void ResetPlayer();

	//----------------------------------------------------------------
	// Regions
	void RegionsContainingPoint(Vector2 point, set<shared_ptr<Region>> & regions);
	void RegionsContainingSegment(Vector2 start, Vector2 end, set<shared_ptr<Region>> & regions);
	void RegionsContainingRect(Rect rect, set<shared_ptr<Region>> & regions);
	shared_ptr<Region> AddNewRegion(int x, int y);
	bool TryGetRegion(int x, int y, shared_ptr<Region> & regions);
	set<shared_ptr<Wall>> CollectWalls(set<shared_ptr<Region>>& regions);
	set<shared_ptr<Sprite>> CollectSprites(set<shared_ptr<Region>>& regions);
};

