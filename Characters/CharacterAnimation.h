#ifndef CHARACTER_ANIMATION_H
#define CHARACTER_ANIMATION_H

#include <Graphics.hpp>
#include "Character.h"
#include <string>
#include <utility>

struct AnimationState
{
  State state;
  unsigned int animation_cpt;
}

class CharacterAnimation : 
{
  public :
    // Constructors
    CharacterAnimation(const KiroGame::Image& sprite_sheet, const AnimationState a);
  
    // Operators
    CharacterAnimation& operator++(); // Continue the current animation
    CharacterAnimation& operator++(int);
    
    void update(); // Same as ++
    
    void setAnimationState(const AnimationState&); 
    
    const sf::Sprite& getSprite() const;
    
  private :
  
    unsigned int m_tick_counter;
    AnimationState m_etat;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::pair<unsigned int, unsigned int> m_sprite_size;
};


#endif
