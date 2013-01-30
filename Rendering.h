#ifndef RENDERING_H
#define RENDERING_H

#include "Maze.h"
#include <utility>
#include <SFML/Graphics.hpp>

namespace rendering
{
	void render_map(const Maze*, sf::RenderWindow&, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size);
	bool secondComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
	bool firstComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
};

#endif