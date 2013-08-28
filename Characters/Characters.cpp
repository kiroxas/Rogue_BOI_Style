#include "Characters.h"

Character::Character(const sf::Image& sprite_sheet, const std::pair<unsigned int,unsigned int>& sprite_size) :
m_sprite_size(sprite_size)
{
   texture.update(sprite_sheet);
   sprite.setTextureRect(sf::IntRect(0, 0, m_sprite_size.first, m_sprite_size.second));
}
