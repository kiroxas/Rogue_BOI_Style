/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#include "CharacterAnimation.h"
#include <utility>

/* A base Class for all characters in the game, hero or foe */
class Character : public sf::Drawable, public sf::Transformable
{
  public :

   Character(const sf::Image& sprite_sheet);

  private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    CharacterAnimation m_animate;
};
