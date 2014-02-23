#ifndef LEVEL_H
#define LEVEL_H

#include "Maze/AbstractMazeGenerator.h"
#include "Maze/NormalMazeGenerator.h"
#include <memory>
#include "Misc/ImagePool.h"
#include "Characters/CollisionManager.h"
#include "Input/Input.h"
#include <functional>
#include <vector>

class Level
{
	public :
    Level(const ImagePool&, Input::GameInput&);

    const Maze& getMaze() const;
    const std::vector<std::shared_ptr<ICharacter>>& getCharacters() const;
    void update();

		
	private :
	std::unique_ptr<Maze> maze;
	const ImagePool& pool;
	CollisionManager* cm;
	std::vector<std::function<void()>> callbacks;
	Input::GameInput& g_i;
	std::vector<std::shared_ptr<ICharacter>> heroes;
};


#endif