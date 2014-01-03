/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnimation.h"
#include <utility>
#include "Hittable.h"
#include <memory>
#include "State.h"
#include "../Misc/Constantes.h"
#include "Bullets.h"
#include <vector>
#include "CollisionManager.h"

/* A base Class for all characters in the game, hero or foe */
class Character : public Hittable, public sf::Drawable
{
  public :

   Character(const KiroGame::Image& sprite_sheet, const CollisionManager& e,float rotation = 0, float scale = 1);
   virtual void update();
   virtual void animate();
   virtual void Move(int x, int y);
   virtual std::pair<unsigned int, unsigned int> getSize() const;
   virtual void shoot();
   virtual ~Character();
   healthType getDamage() const;
   void collide(Hittable*);

  protected :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    State m_state;
    CharacterAnimation m_animate;
    Controls* brain; // The "brain" of the entity, that will give me the next action
    mutable std::vector<Bullets> bullets;
    const CollisionManager& c;
};

#endif
