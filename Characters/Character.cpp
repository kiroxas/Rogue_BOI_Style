#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState()),
brain(nullptr)
{}

void Character::update()
{
	++m_animate;
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = m_animate.getSprite();
	s.setPosition(100,100);

	target.draw(s, states);
}
