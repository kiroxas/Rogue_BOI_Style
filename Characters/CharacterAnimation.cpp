#include "CharacterAnimation.h"

CharacterAnimation::CharacterAnimation(const sf::Image& sprite_sheet, 
                                       const AnimationState a, 
                                       const std::pair<unsigned int, unsigned int>& sprite_size) :
m_etat(a),
m_sprite_size(sprite_size)
{
    if(!m_texture.loadFromImage(sprite_sheet))
    {
    	//Handle Eror
    }
    
}
