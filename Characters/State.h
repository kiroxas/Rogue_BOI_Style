#ifndef STATE_H
#define STATE_H

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

#endif
