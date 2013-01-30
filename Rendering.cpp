/* Rendering.cpp
   File that  contains all the functions for rendering the game.
   Author : Mouton Guillaume (Kiroxas)
*/

#include "Rendering.h"
#include "Room.h"
#include "Constantes.h"

#include <vector>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <sstream>

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
	const float corridors_size = 0.25; // it's corriddors_size % of the blank size
}

void rendering::render_map(const Maze* maze, sf::RenderWindow& screen, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size)
{
	/*
		First let's figure out the layout of the map !
		TODO : This must be done only once for each map, so we have to calculate this when we load a level, 
		not when we render the map
	*/
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
	
	/* Now that we have the layout, let's figure out the size of each element in the map */

	const int minf = std::min_element(positions.begin(),positions.end(),rendering::firstComp)->first; //Minimum for the width
	const int mins = std::min_element(positions.begin(),positions.end(),rendering::secondComp)->second; //Minimum for the height
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
	
	const int line_size_h = blank_height * ::corridors_size;
	const int line_size_w = blank_width * ::corridors_size;
	
	cpt = 0;
	/* Then, let's do the actual rendering */
	
	/* For Debugging purpose, let's log those infos, to see what's messing with the rendering */

	for(auto p : positions)
	{
		sf::RectangleShape rec;
		const unsigned int rank_w = abs(minf - p.first);
		const unsigned int rank_h = abs(mins - p.second);
		const float x = pos.first + rank_w * room_width + (rank_w + 1) * blank_width;
		const float y = pos.second + rank_h * room_height + (rank_h + 1) * blank_height;
		
		/* Just to test, this need to be erased after */
		std::ostringstream oss_x, oss_y, oss_rank_w, oss_rank_h;
		oss_x << x;
		oss_y << y;
		oss_rank_w << rank_w;
		oss_rank_h << rank_h;
		
		infos::log(RENDERING_PATH,"x: " + oss_x.str() + " y: " + oss_y.str() + " rank_w : " + oss_rank_w.str() + " rank_h: "+ oss_rank_h.str());

		rec.setPosition(x,y);
		rec.setSize(sf::Vector2f(room_width,room_height));
		screen.draw(rec);
		
		sf::RectangleShape line; // For corridors between rooms
		
		Room* piece = vec[cpt];
		if(piece == nullptr) 
		{
			infos::log(RENDERING_PATH,"A room is null in render_map, we will not render the rest of the map");
			return;
		}
		
		float x_line, y_line;

		if(piece->getNeighboor(NORTH) != nullptr)
		{
			//If north, the size is the width
			//the (x,y) are located on the square above.
			
			x_line = x + (room_width/2) - (line_size_width / 2);
			y_line = y - blank_height;
			line.setPosition(x_line,y_line);
			line.setSize(sf::Vector2f(line_size_w,blank_height));
			screen.draw(line);
		}
		if(piece->getNeighboor(SOUTH) != nullptr)
		{
			x_line = x + (room_width/2) - (line_size_width / 2);
			y_line = y + room_height;
			line.setPosition(x_line,y_line);
			line.setSize(sf::Vector2f(line_size_w,blank_height));
			screen.draw(line);	
		}
		if(piece->getNeighboor(EAST) != nullptr)
		{
			x_line = x + room_width;
			y_line = y + room_height/2 + line_size_height/2;
			line.setPosition(x_line,y_line);
			line.setSize(sf::Vector2f(blank_width,line_size_h));
			screen.draw(line);	
		}
		if(piece->getNeighboor(WEST) != nullptr)
		{
			x_line = x - blank_width;
			y_line = y + room_height/2 + line_size_height/2;
			line.setPosition(x_line,y_line);
			line.setSize(sf::Vector2f(blank_width,line_size_h));
			screen.draw(line);		
		}
		
	}

	screen.display();
}

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
