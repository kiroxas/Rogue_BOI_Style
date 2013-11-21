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


/* I want a baseClass for Inputs and AI (for example) for being able to switch the too */
class Controls
{
   virtual State nextAction() = 0;
};


/* A base Class for all characters in the game, hero or foe */
class Character : public sf::Drawable, public sf::Transformable
{
  public :

   Character(const KiroGame::Image& sprite_sheet);
   void update();
   void stopAnimation();
   void Move(int x, int y);
   std::pair<unsigned int, unsigned int> getSize() const;

  private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    State m_state;
    CharacterAnimation m_animate;
    Controls* brain; // The "brain" of the entity, that will give me the next action
};

#endif
