/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "CharacterAnimation.h"
#include <utility>
#include <memory>
#include "State.h"
#include "../Misc/Constantes.h"
#include "Bullets.h"
#include <vector>
#include "CollisionManager.h"
#include "ICharacter.h"

/* A base Class for all characters in the game, hero or foe */
class Character : public ICharacter
{
  public :

   Character(const KiroGame::Image& sprite_sheet,CollisionManager* e,float rotation = 0, float scale = 1);
   Character(const KiroGame::Image& sprite_sheet,float rotation = 0, float scale = 0);
   virtual void update();
   virtual void animate();
   virtual void Move(std::pair<int, int>);
   virtual std::pair<unsigned int, unsigned int> getSize() const;
   virtual void shoot();
   virtual sf::FloatRect getGlobalBounds() const;
   virtual ~Character();
   virtual healthType getDamage() const;
   void collide(const Hittable*);
   void setCorrectPosition();
   virtual void setPosition(int x,int y);

  protected :
    Character();
    Character& operator=(Character&&) =delete;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    State m_state;
    CharacterAnimation m_animate;
    mutable std::vector<std::unique_ptr<Bullets>> bullets;
};

#endif
