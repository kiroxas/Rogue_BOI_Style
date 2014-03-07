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
    CharacterAnimation();
    CharacterAnimation(const KiroGame::Image& sprite_sheet, const AnimationState a, float rotation = 0, float scale = 1.0);
  
    // Operators
    CharacterAnimation& operator++(); // Continue the current animation
    CharacterAnimation& operator++(int);
    
    void update(); 
    void animate();
    void setAnimationState(const State&); 
    
    sf::Sprite getSprite() const;
    void AdjustAnimation(const State&);
    std::pair<unsigned int, unsigned int> getSize() const;
    
  private :
  
    sf::Clock m_clock;
    AnimationState m_etat;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::pair<unsigned int, unsigned int> m_sprite_size;
    std::vector<int> m_animation_length;
    bool in_animation;
    bool m_loop;
    float angle;
    float scale;
};


#endif
