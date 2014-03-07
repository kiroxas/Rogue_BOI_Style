#include "Character.h"
#include "../Misc/Constantes.h"
#include <iostream>

Character::Character(const KiroGame::Image& sprite_sheet,CollisionManager* e,float rotation, float scale) :
m_animate(sprite_sheet,AnimationState(),rotation,scale)
{
	m_state.movement = Stand_still;
	m_state.dir = SOUTH;
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> x_distribution(KiroGame::inner_room_pos.first,KiroGame::inner_room_pos.first + KiroGame::inner_room_size.first);
	static std::uniform_int_distribution<int> y_distribution(KiroGame::inner_room_pos.second,KiroGame::inner_room_pos.second + KiroGame::inner_room_size.second);
	setPosition(x_distribution(generator),y_distribution(generator));
	if(e)
	{
	   assignCM(e);
	   setCorrectPosition();
	}
	health = 1;
	attack = 1;
}

Character::Character(const KiroGame::Image& sprite_sheet,float rotation, float scale) :
Character(sprite_sheet,nullptr,rotation,scale)
{}

void Character::setCorrectPosition()
{
   if(!col) return;

	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> x_distribution(KiroGame::inner_room_pos.first,KiroGame::inner_room_pos.first + KiroGame::inner_room_size.first);
	static std::uniform_int_distribution<int> y_distribution(KiroGame::inner_room_pos.second,KiroGame::inner_room_pos.second + KiroGame::inner_room_size.second);

   while(!col->canIMove(this) || !getGlobalBounds().intersects(KiroGame::inner_RoomRect))
		setPosition(x_distribution(generator),y_distribution(generator));
    
}

void Character::Move(std::pair<int, int> p)
{
	int x = p.first;
	int y = p.second;
	auto pos = getPosition();
	auto old_pos = pos;
	pos.x += 2*x;
	pos.y += 2*y;

	setPosition(pos.x,pos.y);
	if(col && !col->canIMove(this))
	{
		setPosition(old_pos.x,old_pos.y);
		return;
	}

	if(x == -1)
		m_state.dir = WEST;
	else if(x == 1)
		m_state.dir = EAST;
	else if(y == -1)
		m_state.dir = NORTH;
	else if(y == 1)
		m_state.dir = SOUTH;

	m_state.movement = Walk;

	m_animate.AdjustAnimation(m_state);
}

void Character::shoot()
{
	int x = getPosition().x,y = getPosition().y;
	auto size = m_animate.getSize();
	switch(m_state.dir)
	{
	   case WEST : x -= 10; break;
	   case EAST : x += size.first; break;
	   case NORTH : y -= 10; break;
	   case SOUTH : y += size.second;
	}
	bullets.emplace_back(new Bullets(std::make_pair(x,y),m_state.dir,col));
}

void Character::update()
{
	m_animate.update();
}

void Character::animate()
{
	m_animate.animate();
}

void Character::setPosition(int x,int y)
{
	sf::Transformable::setPosition(x,y);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(isDead()) return;
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);
	//std::cout << " x : " << getPosition().x << "  y : " <<   getPosition().y << std::endl; 

	for(auto& e : bullets)
	{
		e->update();
	}

	std::for_each(bullets.begin(),bullets.end(),[](const std::unique_ptr<Bullets>& e){if(e.get() && !e->getGlobalBounds().intersects(KiroGame::inner_RoomRect)) e->die(); });
	bullets.erase(std::remove_if(bullets.begin(),bullets.end(),[](const std::unique_ptr<Bullets>& e){if(!e.get()) return true; return e->isDead();}),bullets.end());
	
	for(auto& e : bullets)
	{
		target.draw(*e);
	}
}

std::pair<unsigned int, unsigned int> Character::getSize() const
{
	return m_animate.getSize();
}

Character::Character()
{

}

Hittable::healthType Character::getDamage() const
{
	return attack;
}

void Character::collide(const Hittable* h) 
{
	if(isDead()) return;
	health -= h->getDamage();
	if(isDead() && col) col->unregisterEntity(this);
}

Character::~Character(){}

sf::FloatRect Character::getGlobalBounds() const
{
	sf::Sprite s(m_animate.getSprite());
	s.setPosition(getPosition());
	return s.getGlobalBounds();
}
