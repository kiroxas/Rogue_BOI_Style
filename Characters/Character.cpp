#include "Character.h"
#include "../Misc/Constantes.h"
#include <iostream>

Character::Character(const KiroGame::Image& sprite_sheet,CollisionManager* e,float rotation, float scale) :
m_animate(sprite_sheet,AnimationState(),rotation,scale)
{
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
	health_max = 3;
	attack = 1;
	state = properties::defs::Nothing;

	bullet_ef = BulletEffect::Straight;
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

std::cout << "Set correct pos " << std::endl;
   while(!col->canIMove(this) || !KiroGame::isInInnerRoom(getGlobalBounds()))
		setPosition(x_distribution(generator),y_distribution(generator));
    
}

void Character::Move(std::pair<int, int> p)
{
	int x = p.first;
	int y = p.second;
	auto pos = getPosition();
	//std::cout << " Moving from " << pos.x << " ; " << pos.y << std::endl; 
	auto old_pos = pos;
	pos.x += 2*x;
	pos.y += 2*y;

	setPosition(pos.x,pos.y);
	if(col && !col->canIMove(this))
	{
		if(getPosition() != pos) // something changed its position
			return; 
		//std::cout << "cant move to " << pos.x << " ; " << pos.y << " Resetting to  : " << old_pos.x << " ; " << old_pos.y << " npos : " << n_pos.x << " " << n_pos.y << std::endl;
		setPosition(old_pos.x,old_pos.y);
		return;
	}

	if(x < 0)
		m_state.dir = WEST;
	else if(x > 0)
		m_state.dir = EAST;
	else if(y < 0)
		m_state.dir = NORTH;
	else if(y > 0)
		m_state.dir = SOUTH;
	std::cout << "x : " << x << ", y = " << y << " " << m_state.dir << std::endl;
	m_animate.AdjustAnimation(m_state);
}

void Character::shoot()
{
	int x = getPosition().x,y = getPosition().y;
	auto size = m_animate.getSize();
	auto scale = m_animate.getScale();
	bullets.emplace_back(new Bullets(std::make_pair(x + (size.first * scale.first) /2,y + (size.second * scale.second) /2),m_state.dir,bullet_ef,col));
	bullets.back()->setTeam(this->team_number);
	bullets.back()->setBulletColor(bullet_color);
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
	std::cout << "moving to " << x << " ; " << y << std::endl;
	sf::Transformable::setPosition(x,y);
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(isDead()) return;
	sf::Sprite s = m_animate.getSprite();
	states.transform = getTransform();

	target.draw(s, states);

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

Hittable::healthType Character::getDamage() const
{
	return attack;
}

void Character::collide(Hittable* h) 
{
	if((state & properties::defs::Invincible) == properties::defs::Invincible || isDead()) return;
	health -= h->getDamage();
	
	if(isDead()) col_reg.reset(); // Then we do not want to be in the collision manager anymore
}

Character::~Character(){}

sf::FloatRect Character::getGlobalBounds() const
{
	sf::Sprite s(m_animate.getSprite());
	s.setPosition(getPosition());
	return s.getGlobalBounds();
}
