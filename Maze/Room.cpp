/* Room.cpp
   Implementation file of a room
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Room.h"
#include "../Misc/Constantes.h"
#include "../Characters/Static_Entity.h"
#include "../Characters/eventDecorator.h"
#include <vector>
#include <algorithm>
#include <iostream>

Room::Room(RoomType r,unsigned int n,const ImagePool& p) : 
	number_doors(n),
	canConnect(true),
	type(r),
	pool(p)
{
	std::generate(neighboors.begin(),neighboors.end(),[](){return nullptr; });
}

Room* Room::getNeighboor(Direction dir)
{
	return neighboors[dir];
}

std::vector<Direction> Room::Connectible()
{
	std::vector<Direction> res;

	for(unsigned int i = 0; i < 4; ++i)
	{
		if(neighboors[i] == nullptr) res.push_back(static_cast<Direction>(i));
	}

	return res;
}

bool Room::canHasNeighboor()
{
	return canConnect;
}

void Room::checkConnect()
{
	unsigned int cpt = 0;

	for(const auto& x : neighboors)
	{
		if(x != nullptr) ++cpt;
	}

	if(cpt == number_doors) canConnect = false;
}

bool Room::Connect(Room* r1, Room* r2, Direction dir)
{
	if (r1 == nullptr || r2 == nullptr) return false;
	if (r1->neighboors[dir] != nullptr || r2->neighboors[opposite(dir)] != nullptr) return false;
	if (!r1->canHasNeighboor() || !r2->canHasNeighboor()) return false;

	r1->neighboors[dir] = r2;
	r2->neighboors[opposite(dir)] = r1;

	r1->checkConnect();
	r2->checkConnect();

	return true;
}

std::string GetDoorName(RoomType from, RoomType to)
{
	if (to == BOSS)
		return "boss door";
	else
		return "door";
}

void Room::Fill()
{
	// First lets place Doors !
	
		if(neighboors[NORTH] != nullptr)
		{
			auto door = new Door(pool.getImage(GetDoorName(type,neighboors[NORTH]->type)));
			my_reg.push_back(RoomEmpty::Suscribe(std::bind(&Door::Unlock,std::ref(*door))));
			my_reg.push_back(door->Suscribe(std::bind(&Room::LeftTheRoom,std::ref(*this),NORTH)));
			auto y = KiroGame::room_pos.second;
			auto x = KiroGame::room_pos.first + (KiroGame::room_size.first / 2) - (door->getSize().first / 2);
			door->setPosition(x,y);
			door->setProperties(properties::defs::Invincible);
			doors.emplace_back(door);
		}
		if(neighboors[SOUTH] != nullptr)
		{
			auto door = new Door(pool.getImage(GetDoorName(type,neighboors[SOUTH]->type)),180);
			my_reg.push_back(RoomEmpty::Suscribe(std::bind(&Door::Unlock,std::ref(*door))));
			my_reg.push_back(door->Suscribe(std::bind(&Room::LeftTheRoom,std::ref(*this),SOUTH)));
			auto y = KiroGame::room_pos.second + KiroGame::room_size.second; 
			auto x = KiroGame::room_pos.first + (KiroGame::room_size.first / 2) + (door->getSize().first / 2);
			door->setPosition(x,y);
			door->setProperties(properties::defs::Invincible);
			doors.emplace_back(door);
		}
		if(neighboors[EAST] != nullptr)
		{
			auto door = new Door(pool.getImage(GetDoorName(type,neighboors[EAST]->type)),90);
			my_reg.push_back(RoomEmpty::Suscribe(std::bind(&Door::Unlock,std::ref(*door))));
			my_reg.push_back(door->Suscribe(std::bind(&Room::LeftTheRoom,std::ref(*this),EAST)));
			auto y = KiroGame::room_pos.second + (KiroGame::room_size.second / 2) - (door->getSize().second / 2);
			auto x = KiroGame::room_pos.first + KiroGame::room_size.first; 
			door->setPosition(x,y);
			door->setProperties(properties::defs::Invincible);
			doors.emplace_back(door);
		}
		if(neighboors[WEST] != nullptr)
		{
			auto door = new Door(pool.getImage(GetDoorName(type,neighboors[WEST]->type)),270);
			my_reg.push_back(RoomEmpty::Suscribe(std::bind(&Door::Unlock,std::ref(*door))));
			my_reg.push_back(door->Suscribe(std::bind(&Room::LeftTheRoom,std::ref(*this),WEST)));
			auto y = KiroGame::room_pos.second + (KiroGame::room_size.second / 2) + (door->getSize().second / 2);;
			auto x = KiroGame::room_pos.first;
			door->setPosition(x,y);
			door->setProperties(properties::defs::Invincible);
			doors.emplace_back(door);
		}

	static std::random_device rd;
	static std::mt19937 generator(rd());
	static std::uniform_int_distribution<int> int_distribution(0,15);

	for(int i = 0, end  = int_distribution(generator); i < end; ++i)
	{
  	 	elements.emplace_back(new Static_Entity(pool.getImage("fire")));
   		callbacks.emplace_back(std::bind(&ICharacter::animate,elements.back().get()));
	}
	
}

void Room::update()
{
	for(auto& e : callbacks)
		e();

	std::size_t res = std::count_if(elements.begin(),elements.end(),[](const std::shared_ptr<ICharacter>& e){return e->isDead();});
	if(res == elements.size())
		RoomEmpty::Notify();
}

void Room::addCharacter(std::shared_ptr<ICharacter>& i)
{
	heroes.push_back(i);
}

unsigned long long Room::getNumberOfEnnemies() const
{
	return elements.size();
}

void Room::LeftTheRoom(Direction d)
{
   LeaveRoom::Notify(d);
   my_reg.clear(); // No need to be notified now
}


const std::vector<std::shared_ptr<ICharacter>>& Room::getCharacters() const
{
	return heroes;
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const // Inherited from sf::Drawable
{
	static sf::RectangleShape rec;/*({static_cast<float>(KiroGame::room_pos.first),
								   static_cast<float>(KiroGame::room_pos.second)});*/

	rec.setPosition(KiroGame::room_pos.first,KiroGame::room_pos.second);
	rec.setFillColor(sf::Color(100,100,100,255));
	rec.setSize(sf::Vector2f(KiroGame::room_size.first,KiroGame::room_size.second));
	target.draw(rec);

	sf::RectangleShape rec2;

	rec2.setFillColor(sf::Color(150,150,150,255));
	rec2.setPosition(KiroGame::inner_room_pos.first,KiroGame::inner_room_pos.second);
	rec2.setSize(sf::Vector2f(KiroGame::inner_room_size.first,KiroGame::inner_room_size.second));
	target.draw(rec2);	

	for(auto& e : elements)
	{
		target.draw(*e);
	}

	for(auto& e : doors)
		target.draw(*e);

	for(auto& e: heroes)
		target.draw(*e);
}

bool Room::hasBeenVisited() const
{
	return visited;
}

void Room::setVisited()
{
	visited = true;
}

void Room::assignCM(CollisionManager* c)
{
	for(auto& e : elements)
	{
		e->assignCM(c);
		e->setCorrectPosition();
	}
	for(auto& e : doors)
	{
		e->assignCM(c);
	}
	for(auto& e : heroes)
	{
		e->assignCM(c);
	}
}

void Room::desassignCM()
{
	for(auto&e : elements)
			e->desassignCM();
	for(auto&e : doors)
			e->desassignCM();
	for(auto&e : heroes)
		e->desassignCM();
}

Direction opposite(Direction dir)
{
	switch(dir)
	{
	case NORTH : return SOUTH;
	case EAST : return WEST;
	case WEST : return EAST;
	case SOUTH : return NORTH;
	default : 
		infos::log(MAZE_LOG_PATH,"Unknown Direction in opposite, exiting");
		exit(1);
	}
}
