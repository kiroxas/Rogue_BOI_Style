#include "Maze.h"
#include <random>
#include <list>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <array>

namespace
{
	const int max_ind = 10000;
};

Maze::Maze(unsigned int number, const ImagePool& p) :
	m_numberOfRooms(number),
	m_maze(myMaze(number)),
	pool(p)
{}

Maze::~Maze()
{}


 void Maze::GenerateGraphStructure()
 {
	 // We first create the seed room
	 m_maze.at(0) = god_room.CreateRoom(EMPTY,4,pool);
	 my_room = m_maze.at(0).get();
	 std::vector<std::pair<int,int>> chizu;
	 chizu.push_back(std::make_pair(0,0));
	 unsigned int cpt = 1;

	 static std::random_device rd;
	 static std::mt19937 generator(rd());
  	 static std::bernoulli_distribution distribution(0.5);

	 while(cpt < m_numberOfRooms)
	 {
	 	 std::uniform_int_distribution<int> int_distribution(0,chizu.size()-1);
		 std::pair<int,int> coord = chizu[int_distribution(generator)]; // Get a pos in the map

		 if(distribution(generator))
		 {
			 if(distribution(generator))
			 {
				 coord.first++;
			 }
			 else
			 {
				 coord.first--;
			 }
		 }
		 else
		 {
			 if(distribution(generator))
			 {
				 coord.second++;
			 }
			 else
			 {
				 coord.second--;
			 }
		 }

		 if(std::find(chizu.begin(),chizu.end(),coord) != chizu.end()) continue;

		 std::array<unsigned int, 4> res = find_neighboors(chizu,coord);
		 m_maze.at(cpt) = god_room.CreateRoom(EMPTY,4,pool);
		 unsigned int dir = 0;

		 for(auto& x : res)
		 {
			 if(x != ::max_ind)
			 {
				 Room::Connect(m_maze[cpt].get(),m_maze[x].get(),static_cast<Direction>(dir));
			 }
			 ++dir;
		 }
		 chizu.push_back(coord);
		 ++cpt;
	 }

	 for(auto& e : m_maze)
	 {
	 	e->Fill();
	 }
 }

 void Maze::Go(Direction d)
 {
 	my_room->ResetRoom();
 	my_room = my_room->getNeighboor(d);
 }

 std::array<unsigned int, 4> find_neighboors(const std::vector<std::pair<int, int>>& chizu, const std::pair<int,int>& coord)
 {
	 std::array<unsigned int, 4> res = {{::max_ind,::max_ind,::max_ind,::max_ind}};
	 int cpt = 0;

	 for(auto& x : chizu)
	 {
		 if(x.first == coord.first && x.second == coord.second - 1)
		 {
			 res[SOUTH] = cpt;
		 }
		 else if(x.first == coord.first && x.second == coord.second + 1)
		 {
			 res[NORTH] = cpt;
		 }
		 else if(x.first == coord.first +1 && x.second == coord.second)
		 {
			 res[EAST] = cpt;
		 }
		 else if(x.first == coord.first - 1 && x.second == coord.second)
		 {
			 res[WEST] = cpt;
		 }
		 ++cpt;
	 }

	 return res;
 }

// Go Home Map, you're drunk !
 void Maze::GenerateDrunkStructure()
 {
	 // Come on think of a good algorithm you moron !

	 std::set<unsigned int> rooms_to_connect;
	 std::set<unsigned int> rooms_connected;
	 std::vector<std::pair<unsigned int, unsigned int>> connections;

	 // First We create the Boss Room
	 m_maze.at(0) = god_room.CreateRoom(BOSS,1,pool);
	 rooms_to_connect.insert(0);

	 for(unsigned int i = 1; i < m_numberOfRooms; ++i)
	 {
		 m_maze[i] = god_room.CreateRoom(EMPTY,4,pool);
		 rooms_to_connect.insert(i);
	 }

	 // Connection Time
	 while(rooms_connected.size() != m_numberOfRooms)
	 {
		 // First pick 2 rooms from rooms to connect
		 unsigned int ind, ind2;
		 std::vector<unsigned int> inter(m_numberOfRooms);
		 std::vector<unsigned int>::iterator it;

		 // First let see if we have an intersection between rooms_connected & rooms_to_connect
		 it = std::set_intersection(rooms_connected.begin(), rooms_connected.end(),rooms_to_connect.begin(),rooms_to_connect.end(),inter.begin());

		 // Let choose ind
		 unsigned int number = it - inter.begin();
		 if( number != 0 )
		 {
			 unsigned int ran = rand() % number;
			 ind = inter[ran];
		 }
		 else
		 {
			 unsigned int ran = rand() % rooms_to_connect.size();
			 std::set<unsigned int> :: const_iterator it(rooms_to_connect.begin());
			 advance(it, ran);
			 ind = *it;
		 }

		 // Then let see if we have a difference between rooms_connected & rooms_to_connect
		 it = std::set_difference(rooms_connected.begin(), rooms_connected.end(),rooms_to_connect.begin(),rooms_to_connect.end(),inter.begin());

		 // Let choose ind2
		 number = it - inter.begin();
		 if(number != 0 )
		 {
			 unsigned int ran = rand() % number;
			 ind2 = inter[ran];
		 }
		 else
		 {
			 unsigned int ran = rand() % rooms_to_connect.size();
			 std::set<unsigned int> :: const_iterator it(rooms_to_connect.begin());
			 advance(it, ran);
			 ind2 = *it;
		 }

		 if(ind == ind2) continue;
		 if(std::find(connections.begin(),connections.end(),std::make_pair(ind,ind2)) != connections.end()) continue;
		 if(std::find(connections.begin(),connections.end(),std::make_pair(ind2,ind)) != connections.end()) continue;

		 std::vector<Direction> connec = m_maze[ind2]->Connectible();
		 std::random_shuffle(connec.begin(),connec.end());

		 bool connected = false;
		 for(auto& dir : connec)
		 {
			 if(Room::Connect(m_maze[ind].get(),m_maze[ind2].get(),dir)) 
			 {
				 connected = true;
				 break;
			 }
		 }
		 if(!connected) continue;

		 connections.push_back(std::make_pair(ind,ind2));
		 rooms_connected = find_biggest_connection(connections);
	 }
 }

 std::set<unsigned int> find_biggest_connection(const std::vector<std::pair<unsigned int,unsigned int>>& vec)
 {
	 std::vector<std::set<unsigned int>> res;

	 for(auto& x : vec)
	 {
		 if(res.empty())
		 {
			 std::set<unsigned int> s;
			 s.insert(x.first);
			 s.insert(x.second);
			 res.push_back(s);
		 }
		 else
		 {
			 bool found = false;

			 for(auto& y : res)
			 {
				 if(y.find(x.first) != y.end() || y.find(x.second) != y.end())
				 {
					 y.insert(x.first);
					 y.insert(x.second);
					 found = true;
				 }
			 }

			 if(!found)
			 {
				 std::set<unsigned int> s;
				 s.insert(x.first);
				 s.insert(x.second);
				 res.push_back(s);
			 }
		 }
	 }

	 return *(std::max_element(res.begin(),res.end()));
 }

 Room* Maze::getSeedRoom() const
 {
	 if(m_maze.empty()) return nullptr;

	 return m_maze[0].get();
 }

 unsigned int Maze::getNumberRooms() const
 {
	 return m_numberOfRooms;
 }

Room* Maze::getCurrentRoom() const
{
	return my_room;
}
