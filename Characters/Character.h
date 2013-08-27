/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#include <utility>

/* A base Class for all characters in the game, hero or foe */
class Character : : public sf::Drawable, public sf::Transformable
{
  public :


  private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    sf::Texture m_texture;
};
