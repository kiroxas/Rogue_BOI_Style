#include "Characters.h"

Character::Character(const sf::Image& sprite_sheet, const std::pair<unsigned int,unsigned int>& sprite_size) :
m_animate(sprite_sheet,sprite_size)
{}
