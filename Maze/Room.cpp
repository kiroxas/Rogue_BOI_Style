/* Room.cpp
   Implementation file of a room
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Room.h"
#include "../Misc/Constantes.h"
#include <vector>
#include <algorithm>

Room::Room(RoomType r,unsigned int n,const ImagePool& p,CollisionManager& _c) : 
	type(r),
	number_doors(n),
	canConnect(true),
	pool(p),
	c(_c)
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

void Room::Fill()
{
	// First lets place Doors !
	
		if(neighboors[NORTH] != nullptr)
		{
			elements.emplace_back(new Character(pool.getImage("door"),c));
			auto y = KiroGame::room_pos.second;
			auto x = KiroGame::room_pos.first + (KiroGame::room_size.first / 2) - (elements.back()->getSize().first / 2);
			elements.back()->setPosition(x,y);
		}
		if(neighboors[SOUTH] != nullptr)
		{
			elements.emplace_back(new Character(pool.getImage("angel_door"),c,180));
			auto y = KiroGame::room_pos.second + KiroGame::room_size.second; // - elements.back()->getSize().second;
			auto x = KiroGame::room_pos.first + (KiroGame::room_size.first / 2) + (elements.back()->getSize().first / 2);
			elements.back()->setPosition(x,y);
		}
		if(neighboors[EAST] != nullptr)
		{
			elements.emplace_back(new Character(pool.getImage("door"), c,90));
			auto y = KiroGame::room_pos.second + (KiroGame::room_size.second / 2) - (elements.back()->getSize().second / 2);
			auto x = KiroGame::room_pos.first + KiroGame::room_size.first; // - elements.back()->getSize().first;
			elements.back()->setPosition(x,y);
		}
		if(neighboors[WEST] != nullptr)
		{
			elements.emplace_back(new Character(pool.getImage("door"), c,270));
			auto y = KiroGame::room_pos.second + (KiroGame::room_size.second / 2) + (elements.back()->getSize().second / 2);;
			auto x = KiroGame::room_pos.first;
			elements.back()->setPosition(x,y);
		}
	
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const // Inherited from sf::Drawable
{
	sf::RectangleShape rec;

	rec.setFillColor(sf::Color(100,100,100,255));
	rec.setPosition(KiroGame::room_pos.first,KiroGame::room_pos.second);
	rec.setSize(sf::Vector2f(KiroGame::room_size.first,KiroGame::room_size.second));
	target.draw(rec);

	for(auto& e : elements)
	{
		target.draw(*e);
	}
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
