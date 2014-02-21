#include "Static_Entity.h"
#include <iostream>

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

	setPosition(pos.x,pos.y);
	std::cout << "Move" << std::endl;

	m_animate.AdjustAnimation(m_state);
}

void Static_Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(isDead()) return;
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);
}