#ifndef CHARACTER_DECORATOR
#define CHARACTER_DECORATOR

#include "ICharacter.h"
#include <memory>

class CharacterDecorator : public ICharacter
{
public :
   CharacterDecorator(ICharacter* e);
   virtual ~CharacterDecorator();
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; ;
   virtual sf::FloatRect getGlobalBounds() const;
   virtual std::pair<unsigned int, unsigned int> getSize() const;
   virtual healthType getDamage() const;
   virtual void update();
   virtual void animate();
   virtual void Move(std::pair<int, int> e);
   virtual void shoot();
   virtual void collide(const Hittable* e);
   virtual void setPosition(int,int);
 protected :
   std::unique_ptr<ICharacter> component;
};

#endif
