#pragma once
#include "pch.h"
#include "Wall.h"
#include "Player.h"
#include "Bitmap.h"
#include "Sprite.h"

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
private:

	static const float MOUSE_GAIN;
	shared_ptr<Player> m_player;
	vector<Wall> m_walls;
	set<shared_ptr<Sprite>> m_sprites;
	mutex m_mutex;
	
	map<string, shared_ptr<Bitmap>> m_textures;
	Pixel m_floorColor;
	Pixel m_ceilingColor;
	unique_ptr<Bitmap> m_backBuffer;

	map<char, bool> m_keyStates;
	map<int, bool> m_buttonStates;
private:
	void CreateWallPath(string texture, vector<Vector2> corners);
	void UpdateSprites(double& elapsed);
	void RemoveSprite(shared_ptr<Sprite> sprite);
};

