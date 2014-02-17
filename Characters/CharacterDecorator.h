#ifndef CHARACTER_DECORATOR
#define CHARACTER_DECORATOR

#include "ICharacter.h"
#include <memory>

class CharacterDecorator : public ICharacter
{
public :
   CharacterDecorator(ICharacter* e){component.reset(e);}
   ~CharacterDecorator(){}

 private :
std::unique_ptr<ICharacter> component;
};

#endif
