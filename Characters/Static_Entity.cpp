#include "Static_Entity.h"

Static_Entity::Static_Entity(const KiroGame::Image& sprite_sheet, CollisionManager* e,float rotation, float scale) :
Character(sprite_sheet,e,rotation,scale)
{
	health = 1000;
}

Static_Entity::Static_Entity(const KiroGame::Image& sprite_sheet,float rotation, float scale) :
Character(sprite_sheet,rotation,scale)
{}

void Static_Entity::Move(std::pair<int, int> e)
{
	auto pos = getPosition();
    pos.x += 2*e.first;
    pos.y += 2*e.second;

	setPosition(pos);

	m_animate.AdjustAnimation(m_state);
}
