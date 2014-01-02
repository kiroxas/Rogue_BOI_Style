#include "Character.h"
#include "../Misc/Constantes.h"

Character::Character(const KiroGame::Image& sprite_sheet, const CollisionManager& e,float rotation, float scale) :
Hittable(e),
m_animate(sprite_sheet,AnimationState(),rotation,scale),
brain(nullptr)
{
	m_state.movement = Stand_still;
	m_state.dir = SOUTH;
	//m_animate.RunAnimation(m_state,true);
	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> int_distribution(0,600);
	setPosition(int_distribution(generator),int_distribution(generator));
	col.registerEntity(this);
}

void Character::Move(int x, int y)
{
	auto pos = getPosition();
    pos.x += 2*x;
    pos.y += 2*y;

	setPosition(pos);

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
	bullets.emplace_back(Bullets(std::make_pair(getPosition().x,getPosition().y),m_state.dir,col));
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
		e.update();
	}
	
	//bullets.erase(std::remove_if(bullets.begin(),bullets.end(),[](Bullets& e){return !e.getGlobalBounds().intersects(KiroGame::RoomRect);}),bullets.end());
	for(auto& e : bullets)
	{
		target.draw(e);
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

void Character::collide(Hittable*) 
{}

Character::~Character(){}