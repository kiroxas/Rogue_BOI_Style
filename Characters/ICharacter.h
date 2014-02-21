#ifndef INTERFACE_CHARACTER
#define INTERFACE_CHARACTER

#include <SFML/Graphics.hpp>
#include "Hittable.h"

class ICharacter : public Hittable, public sf::Drawable
{
   public : 
   /* Virtual Destructor */
   ICharacter(){}
   virtual ~ICharacter(){}

   /* Getters */
   virtual healthType getDamage() const {return Hittable::getDamage();}
   virtual std::pair<unsigned int, unsigned int> getSize() const = 0;
   virtual sf::FloatRect getGlobalBounds() const = 0;
   virtual void setPosition(int,int) =0;

   /* Others */
   virtual void update() = 0;
   virtual void animate() = 0;
   virtual void Move(std::pair<int, int>) = 0;
   virtual void shoot() = 0;
   virtual void collide(const Hittable*) =0;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;

   protected :
   virtual void setDamage(healthType e){Hittable::setDamage(e);};
};

#endif