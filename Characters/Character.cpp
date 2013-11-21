#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState()),
brain(nullptr)
{
	m_state.movement = Walk;
	m_state.dir = NORTH;
	//m_animate.RunAnimation(m_state,true);
	setPosition(100,200);
}

void Character::Move(int x, int y)
{
	auto pos = getPosition();
    pos.x += 2*x;
    pos.y += 2*y;

	setPosition(pos);

	if(x == -1)
		m_state.dir = WEST;
	else if(x == 1)
		m_state.dir = EAST;
	else if(y == -1)
		m_state.dir = NORTH;
	else if(y == 1)
		m_state.dir = SOUTH;

	m_animate.AdjustAnimation(m_state);
}

void Character::update()
{
	m_animate.update();
}

void Character::stopAnimation()
{}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);
}

std::pair<unsigned int, unsigned int> Character::getSize() const
{
	return m_animate.getSize();
}