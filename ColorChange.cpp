#include "Header.h"
ColorChange::ColorChange(double pos_x, double pos_y, int m_x, int m_y, BonusType bonustype) : Bonus(pos_x, pos_y, m_x, m_y, bonustype)
{
	
	Action(m_x, m_y);
	img.loadFromFile("resourses/textures/ender_pearl.png");
	img.createMaskFromColor(img.getPixel(0, 0));
	tex.loadFromImage(img);
	BonusTex.setTexture(tex, true);
	setSprite(BonusTex);

}
void ColorChange::Action(int m_x, int m_y) {
	do {
		mat_x = m_x + 2 * (rand() % 3 + 1) - 3;
		mat_y = m_y + 2 * (rand() % 3 + 1) - 3; //rand gem in radius of 3 cells
	} while (mat_x < 0 || mat_x >= 10 || mat_y < 0 || mat_y >= 10);
}