#include "Static_Entity.h"

Static_Entity::Static_Entity(const KiroGame::Image& sprite_sheet, const CollisionManager& e,float rotation, float scale) :
Character(sprite_sheet,e,rotation,scale)
{}

void Static_Entity::Move(int x, int y)
{
	auto pos = getPosition();
    pos.x += 2*x;
    pos.y += 2*y;

	setPosition(pos);

	m_animate.AdjustAnimation(m_state);
}