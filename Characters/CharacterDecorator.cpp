#include "CharacterDecorator.h"

CharacterDecorator::CharacterDecorator(ICharacter* e){component.reset(e);}
CharacterDecorator::~CharacterDecorator(){}
void CharacterDecorator::draw(sf::RenderTarget& target, sf::RenderStates states) const {component->draw(target,states);}
sf::FloatRect CharacterDecorator::getGlobalBounds() const {return component->getGlobalBounds();}
std::pair<unsigned int, unsigned int> CharacterDecorator::getSize() const {return component->getSize();}
void CharacterDecorator::update(){component->update();}
void CharacterDecorator::animate() {component->animate();}
void CharacterDecorator::Move(std::pair<int, int> e) {component->Move(e);}
void CharacterDecorator::shoot() {component->shoot();}
void CharacterDecorator::collide(const Hittable* e){component->collide(e);}
Hittable::healthType CharacterDecorator::getDamage() const {return Hittable::getDamage();};
void CharacterDecorator::setPosition(int x,int y){component->setPosition(x,y);};