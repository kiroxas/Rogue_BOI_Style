#ifndef STATE_H
#define STATE_H

#include "../Misc/Constantes.h"

enum Movement
{
   Stand_still = 0,
   Walk
};

enum ActionState
{
   Doing_nothing = 0,
   Attacking,
   Using_special_object
};

struct State
{
   Movement movement;
   Direction dir;
   ActionState action;

   bool operator==(const State& a) const
   {
      return (movement == a.movement && dir == a.dir && action == a.action);
   }
   bool operator!=(const State& a) const
   {
      return !(*this == a);
   }
};

struct AnimationState
{
  State state;
  int animation_cpt;
};

#endif
