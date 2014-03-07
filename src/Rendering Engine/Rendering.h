#ifndef RENDERING_H
#define RENDERING_H

#include "../Maze/Maze.h"
#include <utility>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Characters/Character.h"
#include "../Misc/GameInfo.h"
#include "../Level.h"

namespace rendering
{
	void render_map(const Maze&, sf::RenderWindow&, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size);
	void render_room(const Room*,sf::RenderWindow&, const std::pair<unsigned int, unsigned int>& pos, const std::pair<unsigned int, unsigned int>& size,const GameInfo& stats);
	void render_level(const Level&, sf::RenderWindow&, const GameInfo& stats);
	void render_characters(const std::vector<std::shared_ptr<ICharacter>>&, sf::RenderWindow&);
	bool secondComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
	bool firstComp(const std::pair<int,int>&  i1, const std::pair<int,int>&  i2);
	void render_time(sf::RenderWindow& screen,const GameInfo& stats);
};

#endif


