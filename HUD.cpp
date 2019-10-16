#include "pch.h"
#include "HUD.h"
#include "Player.h"

#define REGISTER_ICON(item,icon,view) Icons[item] = std::make_shared<Bitmap>(Bitmap::FromFile(string("images/") + icon)); IconMasks[item] = Icons[item]->GetOpaqueBitMask(); Views[item] = std::make_shared<Bitmap>(Bitmap::FromFile(string("images/") + view));

HUD::HUD(Player* player) : m_player(player)
{
	REGISTER_ICON("key.bmp", "key_icon.bmp", "");
	REGISTER_ICON("knife.bmp", "knife_icon.bmp", "knife_view.bmp");
	REGISTER_ICON("shotgun.bmp", "shotgun_icon.bmp", "shotgun_view.bmp");

	m_healthyFace = std::make_shared<Bitmap>(Bitmap::FromFile("images/healthy_face.bmp"));
	m_damagedFace = std::make_shared<Bitmap>(Bitmap::FromFile("images/damaged_face.bmp"));
	m_unhealthyFace = std::make_shared<Bitmap>(Bitmap::FromFile("images/unhealthy_face.bmp"));

	m_stipple = Bitmap::FromFile("images/stipple.bmp").GetOpaqueBitMask();
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
	renderFace(windowWidth, windowHeight);
	//addIcons(sizeOfBottom, yPadding, xPadding);
}

void HUD::addReticle(int windowWidth, int windowHeight)
{
	reticle.renderReticle(windowWidth, windowHeight, m_player->AttackTimer / m_player->AttackCooldown);
}

void HUD::renderActiveItem(int windowWidth, int windowHeight)
{
	if (Views.count(m_player->ActiveItem)) {
		const float scale = ((float)windowHeight / 128.f) * 0.5;
		glPixelZoom(scale, scale);
		auto& view = *Views[m_player->ActiveItem];
		
		glRasterPos2i(windowWidth / 2 - view.GetWidth() * scale / 2,0);
		glDrawPixels(view.GetWidth(), view.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)view.GetPixels());
	}
}

void HUD::renderFace(int windowWidth, int windowHeight)
{
	shared_ptr<Bitmap> face;
	float percentHealth = m_player->Health / Player::MaxHealth;
	if (percentHealth > 2.f / 3.f) {
		face = m_healthyFace;
	}
	else if (percentHealth > 1.f / 3.f) {
		face = m_damagedFace;
	}
	else {
		face = m_unhealthyFace;
	}
	static const float scale = 1.f;
	glPixelZoom(scale, scale);
	glRasterPos2i(windowWidth / 2 - face->GetWidth() * scale / 2, 0);
	glDrawPixels(face->GetWidth(), face->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)face->GetPixels());
	

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
	glPixelZoom(1, 1);

	int i = 0;
	for (auto iconEntry : Icons) {
		auto & icon = *iconEntry.second;
		int left = i * icon.GetWidth() + (xPadding / 2.0);
		int right = left + icon.GetWidth();
		int top = sizeOfBottom - (yPadding / 2.0);
		int bottom = yPadding / 2.0;
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(&m_stipple[0]);
		glEnd();
		
		glBegin(GL_POLYGON);

		glColor4f(0, 0, 0,0.5f);
		glVertex2d(left, top);
		glVertex2d(right, top);
		glVertex2d(right, bottom);
		glVertex2d(left, bottom);

		glEnd();
		glDisable(GL_POLYGON_STIPPLE);
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
