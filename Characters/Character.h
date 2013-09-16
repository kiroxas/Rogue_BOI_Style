/*  Character.h
   File that defines a character
   author : Mouton Guillaume (Kiroxas)
*/

#include "CharacterAnimation.h"
#include <utility>

enum MovingState
{
   Stand_still = 0,
   Walk_down,
   Walk_up,
   Walk_left,
   Walk_right
};

enum ActionState
{
   Doing_nothing = 0,
   Attacking,
   Using_special_object
};

struct State
{
   MovingState m_movement;
   ActionState m_action;
};


/* I want a baseClass for Inputs and AI (for example) for being able to switch the too */
Class Controls
{
   State nextAction() = 0;
};



/* A base Class for all characters in the game, hero or foe */
class Character : public sf::Drawable, public sf::Transformable
{
  public :

   Character(const sf::Image& sprite_sheet);

  private :
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Inherited from sf::Drawable

    CharacterAnimation m_animate;
    std::unique_ptr<Controls> brain; // The "brain" of the entity, that will give me the next action
};
