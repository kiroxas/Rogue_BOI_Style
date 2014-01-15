#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet,CollisionManager* e,float rotation, float scale) :
Hittable(e),
m_animate(sprite_sheet,AnimationState(),rotation,scale)
{
	m_state.movement = Stand_still;
	m_state.dir = SOUTH;
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> int_distribution(0,600);
	setPosition(int_distribution(generator),int_distribution(generator));
	if(col)
	   col->registerEntity(this);
	health = 1;
	attack = 1;
}

Character::Character(const KiroGame::Image& sprite_sheet,float rotation, float scale) :
Hittable(),
m_animate(sprite_sheet,AnimationState(),rotation,scale)
{
	m_state.movement = Stand_still;
	m_state.dir = SOUTH;
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> int_distribution(0,600);
	setPosition(int_distribution(generator),int_distribution(generator));
	if(col)
	   col->registerEntity(this);
	health = 1;
	attack = 1;
}


void Character::Move(int x, int y)
{
	auto pos = getPosition();
	auto old_pos = pos;
	pos.x += 2*x;
	pos.y += 2*y;

	setPosition(pos);
	if(col && !col->canIMove(this))
	{
		setPosition(old_pos);
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
	   case WEST : x -= 7; break;
	   case EAST : x += size.first; break;
	   case NORTH : y -= 7; break;
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

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);

	for(auto& e : bullets)
	{
		e->update();
	}
	
	bullets.erase(std::remove_if(bullets.begin(),bullets.end(),[](const std::unique_ptr<Bullets>& e){return e->isDead();}),bullets.end());
	bullets.erase(std::remove_if(bullets.begin(),bullets.end(),[](const std::unique_ptr<Bullets>& e){return !e->getGlobalBounds().intersects(KiroGame::RoomRect);}),bullets.end());
	for(auto& e : bullets)
	{
		target.draw(*e);
	}
}

std::pair<unsigned int, unsigned int> Character::getSize() const
{
	return m_animate.getSize();
}

Hittable::healthType Character::getDamage() const
{
	return attack;
}

void Character::collide(const Hittable* h) 
{
	health -= h->getDamage();
}

Character::~Character(){}

sf::FloatRect Character::getGlobalBounds() const
{
	sf::Sprite s(m_animate.getSprite());
	s.setPosition(getPosition());
	return s.getGlobalBounds();
}
