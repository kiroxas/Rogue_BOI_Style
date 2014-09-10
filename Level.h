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

class Level : public Suscribable<Events::HeroAreDead, void(void)>
{
	public :
	using Hero_type = std::shared_ptr<ICharacter>;
    Level(const ImagePool&, Input::GameInput&);

    const Maze& getMaze() const;
    const std::vector<std::shared_ptr<ICharacter>>& getCharacters() const;
    void update();
    void ReAssignRoom(Direction d);
		
	private :
	std::unique_ptr<Maze> maze;
	const ImagePool& pool;
	CollisionManager* cm;
	Input::GameInput& g_i;
	std::vector<Hero_type> heroes;
	Registration hero_move, hero_shoot, assign_room;
	std::vector<std::function<void()>> callbacks;
};


#endif