#ifndef STATE_H
#define STATE_H

#include "../Misc/Constantes.h"

enum ActionState
{
   Doing_nothing = 0,
   Attacking,
   Using_special_object
};

struct State
{
   Direction dir;
   ActionState action;

   bool operator==(const State& a) const
   {
      return (dir == a.dir && action == a.action);
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
