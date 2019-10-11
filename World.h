#pragma once
#include "pch.h"
#include "Wall.h"
#include "Player.h"
#include "Bitmap.h"
#include "Sprite.h"

class World
{
public:
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
	vector<shared_ptr<Sprite>> m_sprites;
	map<char, bool> m_keyStates;
	map<int, bool> m_buttonStates;
	Vector2 m_mouseDelta;
	Vector2 m_lastMousePos;
	mutex m_mutex;
	
	map<string, shared_ptr<Bitmap>> m_textures;
	Pixel m_floorColor;
	Pixel m_ceilingColor;
	unique_ptr<Bitmap> m_backBuffer;
private:
	bool GetLineIntersection(Vector2 startA, Vector2 dirA, Vector2 startB, Vector2 dirB, float& tA, float& tB);
	Vector2 GetVectorToSegment(Vector2 start, Vector2 end, Vector2 point);
	void CreateWallPath(string texture, vector<Vector2> corners);
	void UpdateSpritePositions(double& elapsed);
};

