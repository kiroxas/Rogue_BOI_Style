#ifndef STATE_H
#define STATE_H

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
};

struct AnimationState
{
  State state;
  unsigned int animation_cpt;
};

#endif
