#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState()),
brain(nullptr)
{}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{}
