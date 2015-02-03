#ifndef LEVEL_H
#define LEVEL_H

#include "Maze/AbstractMazeGenerator.h"
#include "Maze/NormalMazeGenerator.h"
#include <memory>
#include "Misc/ImagePool.h"
#include "Misc/GameInfo.h"
#include "Characters/CollisionManager.h"
#include "Input/Input.h"
#include <functional>
#include <vector>

class Level : public Suscribable<Events::HeroAreDead, void(void)>,
			  public Suscribable<Events::ClearedLevel, void(void)>
{
	public :

	using HeroAreDead = Suscribable<Events::HeroAreDead, void(void)>;
	using ClearedLevel = Suscribable<Events::ClearedLevel, void(void)>;
	using Hero_type = std::unique_ptr<ICharacter>;
	
    Level(const ImagePool&, Input::GameInput&, GameInfo&);

    const Maze& getMaze() const;
    std::vector<Hero_type> getCharacters();
    const std::vector<Hero_type>& peekAtCharacters() const;
    void update();
    void ReAssignRoom(Direction d);
		
	private :
	std::unique_ptr<Maze> maze;
	const ImagePool& pool;
	CollisionManager* cm;
	Input::GameInput& g_i;
	//std::vector<Hero_type> heroes;
	Registration hero_move, hero_shoot, assign_room, exit_level;
	std::vector<std::function<void()>> callbacks;
	GameInfo& stats;
};


#endif
