#include "pch.h"
#include "HUD.h"
#include "Player.h"

#define REGISTER_ICON(item,icon,view) Icons[item] = std::make_shared<Bitmap>(Bitmap::FromFile(string("images/") + icon)); IconMasks[item] = Icons[item]->GetOpaqueBitMask(); Views[item] = std::make_shared<Bitmap>(Bitmap::FromFile(string("images/") + view));

HUD::HUD(Player* player) : m_player(player)
{
	REGISTER_ICON("key.bmp", "key_icon.bmp", "");
	REGISTER_ICON("knife.bmp", "knife_icon.bmp", "knife_view.bmp");
	REGISTER_ICON("shotgun.bmp", "shotgun_icon.bmp", "shotgun_view.bmp");
}


void HUD::render(int windowWidth, int windowHeight)
{
	
	float yPadding = 0.01 * windowHeight;
	float xPadding = 0.01 * windowWidth;
	float sizeOfBottom = 128 + yPadding;
	addReticle(windowWidth, windowHeight);
	renderActiveItem(windowWidth, windowHeight);
	bottomBackground(sizeOfBottom, yPadding, xPadding, windowWidth, windowHeight);
	addTiles(sizeOfBottom, yPadding, xPadding, windowWidth, windowHeight);
	//addIcons(sizeOfBottom, yPadding, xPadding);
}

void HUD::addReticle(int windowWidth, int windowHeight)
{
	reticle.renderReticle(windowWidth, windowHeight, m_player->AttackTimer / m_player->AttackCooldown);
}

void HUD::renderActiveItem(int windowWidth, int windowHeight)
{
	if (Views.count(m_player->ActiveItem)) {
		static const int scale = 2;
		glPixelZoom(scale, scale);
		auto& view = *Views[m_player->ActiveItem];
		int scaledImageWidth = view.GetWidth() * scale;
		int scaledImageHeight = view.GetHeight() * scale;
		
		glRasterPos2i(windowWidth / 2 - scaledImageWidth / 2,0);
		glDrawPixels(view.GetWidth(), view.GetWidth(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)view.GetPixels());
		glPixelZoom(1, 1);
	}
}

void HUD::renderFace(int windowWidth, int windowHeight)
{
}

void HUD::bottomBackground(float& sizeOfBottom, float& yPadding, float& xPadding, int windowWidth, int windowHeight)
{
	glColor4f(115.0 / 255.0, 111.0 / 255.0, 101.0 / 255.0, 0.5f);

	glBegin(GL_POLYGON);

	glVertex2d(0, sizeOfBottom);
	glVertex2d(windowWidth, sizeOfBottom);
	glVertex2d(windowWidth, 0);
	glVertex2d(0, 0);

	glEnd();

	glColor4f(1, 1, 1,0.5f);
	glLineWidth(5);
	glBegin(GL_LINES);

	//Top bar
	glVertex2d(0, sizeOfBottom + (yPadding / 2.0));
	glVertex2d(windowWidth, sizeOfBottom + (yPadding / 2.0));

	glEnd();
}

void HUD::addTiles(float& sizeOfBottom, float& yPadding, float& xPadding, int windowWidth, int windowHeight)
{
	

	int i = 0;
	for (auto iconEntry : Icons) {
		auto & icon = *iconEntry.second;
		int left = i * icon.GetWidth() + (xPadding / 2.0);
		int right = left + icon.GetWidth();
		int top = sizeOfBottom - (yPadding / 2.0);
		int bottom = yPadding / 2.0;
		glBegin(GL_POLYGON);

		glColor4f(0, 0, 0,0.5f);
		glVertex2d(left, top);
		glVertex2d(right, top);
		glVertex2d(right, bottom);
		glVertex2d(left, bottom);

		glEnd();
		glRasterPos2d(left, bottom);
		if (m_player->Inventory[iconEntry.first] > 0) {
			glDrawPixels(icon.GetWidth(), icon.GetWidth(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)icon.GetPixels());
		}
		else {
			// The player does not have this item, so render a flat color version of the full color icon
			auto & mask = IconMasks[iconEntry.first];
			glColor3f(0.1f, 0.1f, 0.1f);
			glBitmap(icon.GetWidth(),icon.GetHeight(), 0, 0, 0, 0, &mask[0]);
		}
		i++;
		
	}
}
