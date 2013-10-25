#include "Character.h"

Character::Character(const KiroGame::Image& sprite_sheet) :
m_animate(sprite_sheet,AnimationState())
{}
