#ifndef CHARACTER_ANIMATION_H
#define CHARACTER_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include "../Misc/Constantes.h"
#include "State.h"

class CharacterAnimation 
{
  public :
    // Constructors
    CharacterAnimation(const KiroGame::Image& sprite_sheet, const AnimationState a);
  
    // Operators
    CharacterAnimation& operator++(); // Continue the current animation
    CharacterAnimation& operator++(int);
    
    void update(); // Same as ++
    
    void setAnimationState(const AnimationState&); 
    
    sf::Sprite getSprite() const;
    
  private :
  
    unsigned int m_tick_counter;
    AnimationState m_etat;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::pair<unsigned int, unsigned int> m_sprite_size;
};


#endif
