#ifndef CHARACTER_ANIMATION_H
#define CHARACTER_ANIMATION_H

#include <Image.hpp>
#include <Texture.hpp>

class CharacterAnimation : 
{
  public :
    // Constructors
    CharacterAnimation(const sf::Image& sprite_sheet, const AnimationState a, const std::pair<unsigned int, unsigned int>& sprite_size);
  
    // Operators
    CharacterAnimation& operator++(); // Continue the current animation
    CharacterAnimation& operator++(int);
    
    void update(); // Same as ++
    
    void setAnimationState(const AnimationState); 
    
    const sf::Sprite& getSprite() const;
    
  private :
  
    unsigned int m_tick_counter;
    Animationstate m_etat;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::pair<unsigned int, unsigned int> m_sprite_size;
};


#endif
