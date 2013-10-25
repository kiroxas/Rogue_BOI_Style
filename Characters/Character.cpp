#include "Character.h"

Character::Character(const sf::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState())
{}
