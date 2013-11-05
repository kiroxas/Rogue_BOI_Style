#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState()),
brain(nullptr)
{
	AnimationState a;
	a.state.movement = Stand_still;
	m_animate.RunAnimation(a,true);
	setPosition(100,200);
}

void Character::Move(int x, int y)
{
	auto pos = getPosition();
	pos.x += x;
	pos.y += y;

	setPosition(pos);
}

void Character::update()
{
	m_animate.update();
}

void Character::stopAnimation()
{
	m_animate.switchAnimationLoop();
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);
}
