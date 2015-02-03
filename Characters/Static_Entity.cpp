#include "Static_Entity.h"
#include <iostream>

Static_Entity::Static_Entity(const KiroGame::Image& sprite_sheet, CollisionManager* e,float rotation, float scale) :
Character(sprite_sheet,e,rotation,scale)
{
	health = 1;
}

Static_Entity::Static_Entity(const KiroGame::Image& sprite_sheet,float rotation, float scale) :
Character(sprite_sheet,rotation,scale)
{
	health = 1;
}

void Static_Entity::Move(std::pair<int, int> e)
{
	auto pos = getPosition();
	auto old_pos = pos;
    pos.x += 2*e.first;
    pos.y += 2*e.second;
    std::cout << " SE Moving from " << pos.x << " ; " << pos.y << std::endl; 
    setPosition(pos.x,pos.y);

    if(col && !col->canIMove(this))
	{
		setPosition(old_pos.x,old_pos.y);
		return;
	}

	m_animate.AdjustAnimation(m_state);
}

void Static_Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(isDead()) return;
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);
}
