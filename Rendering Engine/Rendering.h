#ifndef RENDERING_H
#define RENDERING_H

#include "../Maze/Maze.h"
#include <utility>
#include <Graphics.hpp>

namespace rendering
{
	void render_map(const Maze*, sf::RenderWindow&, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size);
	void render_room(const Room*,sf::RenderWindow&, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size);
	void render_level(const Maze*, sf::RenderWindow&);
	bool secondComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
	bool firstComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
};

#endif
