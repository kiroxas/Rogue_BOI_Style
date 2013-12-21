/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnimation.h"
#include <utility>
#include <SFML/Graphics.hpp>
#include <memory>
#include "State.h"
#include "../Misc/Constantes.h"
#include "Bullets.h"
#include <vector>

/* A base Class for all characters in the game, hero or foe */
class Character : public sf::Drawable, public sf::Transformable
{
  public :

   Character(const KiroGame::Image& sprite_sheet, float rotation = 0, float scale = 1);
   virtual void update();
   virtual void animate();
   virtual void Move(int x, int y);
   virtual std::pair<unsigned int, unsigned int> getSize() const;
   virtual void shoot();

  protected :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    State m_state;
    CharacterAnimation m_animate;
    mutable std::vector<Bullets> bullets;
};

#endif
