#include "Rendering.h"
#include "Room.h"
#include "Constantes.h"

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>

/* render_map
   maze : The maze that needs to be rendered
   screen : The screen where to render the maze
   pos : Position on the screen where to render the map
   size : size of the map
*/

namespace
{
	const int quad_for_rooms = 4;
	const int quad_for_blanks = 1;
	const int quad = quad_for_rooms + quad_for_blanks;
}

void rendering::render_map(const Maze* maze, sf::RenderWindow& screen, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size)
{
	Room* seed = maze->getSeedRoom();

	std::vector<Room*> vec;
	std::vector<std::pair<int, int>> positions;
	std::vector<std::pair<unsigned int, unsigned int>> coords;

	positions.push_back(std::make_pair(0,0));
	coords.push_back(std::make_pair(pos.first + size.first/2, pos.second + size.second / 2));

	unsigned int cpt = 0;
	vec.push_back(seed);

	while(cpt < vec.size())
	{
		Room* piece = vec[cpt];

		if(piece == nullptr) 
		{
			infos::log(RENDERING_PATH,"A room is null in render_map, we will not render the rest of the map");
			return;
		}

		if(piece->getNeighboor(NORTH) != nullptr)
		{
			if (std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second - 1)) == positions.end())
			{
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second - 1));
				vec.push_back(piece->getNeighboor(NORTH));
			}
		}
		if (piece->getNeighboor(SOUTH) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second + 1)) == positions.end())
			{
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second + 1));
				vec.push_back(piece->getNeighboor(SOUTH));
			}
		}
		if (piece->getNeighboor(WEST) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first - 1,positions[cpt].second)) == positions.end())
			{
				positions.push_back(std::make_pair(positions[cpt].first - 1,positions[cpt].second));
				vec.push_back(piece->getNeighboor(WEST));
			}
		}
		if (piece->getNeighboor(EAST) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first + 1,positions[cpt].second)) == positions.end())
			{
				positions.push_back(std::make_pair(positions[cpt].first + 1,positions[cpt].second));
				vec.push_back(piece->getNeighboor(EAST));
			}
		}

		++cpt;
	}

	const int minf = std::min_element(positions.begin(),positions.end(),rendering::firstComp)->first;
	const int mins = std::min_element(positions.begin(),positions.end(),rendering::secondComp)->second;
	const int maxf = std::max_element(positions.begin(),positions.end(),rendering::firstComp)->first;
	const int maxs = std::max_element(positions.begin(),positions.end(),rendering::secondComp)->second;

	const int number_room_w = maxs - mins + 1;
	const int number_room_h = maxf - minf + 1;
	const int width_for_rooms = (static_cast<float>(size.first) / ::quad) * ::quad_for_rooms; // Takes quad_for_rooms/quad % of the full size
	const int height_for_rooms = (static_cast<float>(size.second) / ::quad) * ::quad_for_rooms; 
	const int width_for_blanks = (static_cast<float>(size.first) / ::quad) * ::quad_for_blanks;
	const int height_for_blanks = (static_cast<float>(size.second) / ::quad) * ::quad_for_blanks;

	const float room_height = height_for_rooms / number_room_h;
	const float room_width = width_for_rooms / number_room_w;
	const float blank_height = height_for_blanks / (number_room_h + 1);
	const float blank_width = width_for_blanks / (number_room_w + 1);

	for(auto p : positions)
	{
		sf::RectangleShape rec;
		const unsigned int rank_w = abs(minf - p.first);
		const unsigned int rank_h = abs(mins - p.second);
		const float x = pos.first + rank_w * room_width + (rank_w + 1) * blank_width;
		const float y = pos.second + rank_h * room_height + (rank_h + 1) * blank_height;

		rec.setPosition(x,y);
		rec.setSize(sf::Vector2f(room_width,room_height));
		screen.draw(rec);
	}

	screen.display();
}

/*
void rendering::render_map(const Maze* maze, sf::RenderWindow& screen, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size)
{

	Room* seed = maze->getSeedRoom();
	//const unsigned int n_rooms = maze->getNumberRooms();
	//const int room_height = size.second / static_cast<int>(1.5* n_rooms);
	//const int room_width = size.first / static_cast<int>(1.5* n_rooms);
	std::vector<Room*> vec;
	std::vector<std::pair<int, int>> positions;
	std::vector<std::pair<unsigned int, unsigned int>> coords;
	positions.push_back(std::make_pair(0,0));
	coords.push_back(std::make_pair(pos.first + size.first/2, pos.second + size.second / 2));

	unsigned int cpt = 0;
	vec.push_back(seed);

	const unsigned int constante = 20;

	while(cpt < vec.size())
	{
		Room* piece = vec[cpt];
		//sf::RectangleShape rec;
		//rec.setPosition(static_cast<float>(coords[cpt].first - static_cast<int>(room_width / 2)), static_cast<float>(coords[cpt].second - static_cast<int>(room_height / 2)));
		//rec.setSize(sf::Vector2f(static_cast<float>(room_width),static_cast<float>(room_height)));

		//screen.draw(rec);

		if(piece == nullptr) 
		{
			infos::log(RENDERING_PATH,"A room is empty in render_map, we will not render the rest of the map");
			return;
		}

		//sf::RectangleShape line;
		//line.setPosition(static_cast<float>(coords[cpt].first), static_cast<float>(coords[cpt].second));

		if(piece->getNeighboor(NORTH) != nullptr)
		{
			if (std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second - 1)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(NORTH));
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second - 1));
				//coords.push_back(std::make_pair(coords[cpt].first,coords[cpt].second - room_height - constante));
			}
			//line.setSize(sf::Vector2f(static_cast<float>(room_width / 8), static_cast<float>(-room_height) ));
			//screen.draw(line);
		}
		if (piece->getNeighboor(SOUTH) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second + 1)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(SOUTH));
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second + 1));
				//coords.push_back(std::make_pair(coords[cpt].first,coords[cpt].second + room_height + constante));
			}
			//line.setSize(sf::Vector2f( static_cast<float>(room_width / 8), static_cast<float>(room_height) ));
			//screen.draw(line);
		}
		if (piece->getNeighboor(WEST) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first - 1,positions[cpt].second)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(WEST));
				positions.push_back(std::make_pair(positions[cpt].first - 1,positions[cpt].second));
				//coords.push_back(std::make_pair(coords[cpt].first - room_width - constante,coords[cpt].second));
			}
			//line.setSize(sf::Vector2f(static_cast<float>(-room_width), static_cast<float>(room_width /8) ));
			//screen.draw(line);
		}
		if (piece->getNeighboor(EAST) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first + 1,positions[cpt].second)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(EAST));
				positions.push_back(std::make_pair(positions[cpt].first + 1,positions[cpt].second));
				//coords.push_back(std::make_pair(coords[cpt].first + room_width + constante,coords[cpt].second));
			}
		}

		++cpt;
	}

	int minf = std::min_element(positions.begin(),positions.end(),rendering::firstComp)->first;
	int mins = std::min_element(positions.begin(),positions.end(),rendering::secondComp)->second;
	int maxf = std::max_element(positions.begin(),positions.end(),rendering::firstComp)->first;
	int maxs = std::max_element(positions.begin(),positions.end(),rendering::secondComp)->second;

	const int room_height = (size.second )/  static_cast<int>(maxs-mins +1);
	const int room_width = size.first / static_cast<int>(maxf - minf +1);

	cpt = 0;
	vec.clear();
	vec.push_back(seed);
	positions.clear();
	positions.push_back(std::make_pair(0,0));
	
	while(cpt < vec.size())
	{
		Room* piece = vec[cpt];
		sf::RectangleShape rec;
		rec.setPosition(static_cast<float>(coords[cpt].first - static_cast<int>(room_width / 2)), static_cast<float>(coords[cpt].second - static_cast<int>(room_height / 2)));
		rec.setSize(sf::Vector2f(static_cast<float>(room_width),static_cast<float>(room_height)));

		screen.draw(rec);

		if(piece == nullptr) 
		{
			infos::log(RENDERING_PATH,"A room is empty in render_map, we will not render the rest of the map");
			return;
		}

		sf::RectangleShape line;
		line.setPosition(static_cast<float>(coords[cpt].first), static_cast<float>(coords[cpt].second));

		if(piece->getNeighboor(NORTH) != nullptr)
		{
			if (std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second - 1)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(NORTH));
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second - 1));
				vec.push_back(piece->getNeighboor(NORTH));
			//	positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second - 1));
				coords.push_back(std::make_pair(coords[cpt].first,coords[cpt].second - room_height - constante));
			}
			
			line.setSize(sf::Vector2f(static_cast<float>(room_width / 8), static_cast<float>(-room_height) ));
			screen.draw(line);
		}
		if (piece->getNeighboor(SOUTH) != nullptr)
		{
		 
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first,positions[cpt].second + 1)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(SOUTH));
				positions.push_back(std::make_pair(positions[cpt].first,positions[cpt].second + 1));
				vec.push_back(piece->getNeighboor(SOUTH));
				coords.push_back(std::make_pair(coords[cpt].first,coords[cpt].second + room_height + constante));
			}
			
			line.setSize(sf::Vector2f( static_cast<float>(room_width / 8), static_cast<float>(room_height) ));
			screen.draw(line);
		}
		if (piece->getNeighboor(WEST) != nullptr)
		{
			
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first - 1,positions[cpt].second)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(WEST));
				positions.push_back(std::make_pair(positions[cpt].first - 1,positions[cpt].second));
				vec.push_back(piece->getNeighboor(WEST));
				//positions.push_back(std::make_pair(positions[cpt].first - 1,positions[cpt].second));
				coords.push_back(std::make_pair(coords[cpt].first - room_width - constante,coords[cpt].second));
			}
			
			line.setSize(sf::Vector2f(static_cast<float>(-room_width), static_cast<float>(room_width /8) ));
			screen.draw(line);
		}
		if (piece->getNeighboor(EAST) != nullptr)
		{
			if(std::find(positions.begin(),positions.end(),std::make_pair(positions[cpt].first + 1,positions[cpt].second)) == positions.end())
			{
				//vec.push_back(piece->getNeighboor(EAST));
				positions.push_back(std::make_pair(positions[cpt].first + 1,positions[cpt].second));
			
				vec.push_back(piece->getNeighboor(EAST));
				//positions.push_back(std::make_pair(positions[cpt].first + 1,positions[cpt].second));
				coords.push_back(std::make_pair(coords[cpt].first + room_width + constante,coords[cpt].second));
			}
			
			line.setSize(sf::Vector2f(static_cast<float>(room_width), static_cast<float>(room_width / 8) ));
			screen.draw(line);
		}

		++cpt;
	}

	screen.display();
}
*/

bool rendering::firstComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2)
{
	if(i1.first < i2.first)
		return true;

	return false;
}

bool rendering::secondComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2)
{
	if(i1.second < i2.second)
		return true;

	return false;
}