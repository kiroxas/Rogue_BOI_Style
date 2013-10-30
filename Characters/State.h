#ifndef STATE_H
#define STATE_H

enum MovingState
{
   Stand_still = 0,
   Stand_still_up,
   Stand_still_left,
   Stand_still_right,
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
   MovingState movement;
   ActionState action;
};

struct AnimationState
{
  State state;
  unsigned int animation_cpt;
};

#endif
