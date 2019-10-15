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
	friend class Sprite;
	friend class Player;
	friend class Item;
	World();
	void Update(double& elapsed);
	void Render();
	void UpdateKeyState(char key, bool state);
	void UpdateButtonState(int button, bool state);
	void UpdateMousePosition(Vector2 position);
	Bitmap& GetTexture(string name);
	void UpdateBackBuffer(int width, int height);
	
	
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
	
private:

	static const float MOUSE_GAIN;
	static const float REGION_WIDTH;
	static const float UPDATE_RANGE;
	map<int, map<int, shared_ptr<Region>>> m_regions;

	Vector2 m_mousePosition;

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


private:
	
	//----------------------------------------------------------------
	// Rendering
	void RenderPerspective();
	void RenderHUD();
	void RenderMenu();

	//----------------------------------------------------------------
	// Updating
	void UpdateSprites(double& elapsed, set<shared_ptr<Sprite>>& sprites);
	void UpdateWalls(double& elapsed, set<shared_ptr<Wall>>& walls);

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

