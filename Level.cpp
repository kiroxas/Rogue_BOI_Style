#include "Level.h"
#include "Characters/Character.h"

Level::Level(const ImagePool& p, Input::GameInput& gi) :
pool(p),
cm(new CollisionManager()),
g_i(gi)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> int_distribution(0,10);

	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(pool));
	maze = (g->CreateMaze(int_distribution(generator)));
	maze->getCurrentRoom()->assignCM(cm);
	heroes.emplace_back(std::make_shared<Character>(pool.getImage("isaac"),cm));
	g_i.Suscribe(Events::Move(),std::bind(&ICharacter::Move,heroes.back().get(),std::placeholders::_1));
	g_i.Suscribe(Events::Shoot(),std::bind(&ICharacter::shoot,heroes.back().get()));

	for(auto& e : heroes)
		maze->getCurrentRoom()->addCharacter(e);
}

const Maze& Level::getMaze() const
{
	return *maze;
}

const std::vector<std::shared_ptr<ICharacter>>& Level::getCharacters() const
{
	return maze->getCurrentRoom()->getCharacters();
}

void Level::update()
{
	maze->getCurrentRoom()->update();
	for(auto e: callbacks)
		e();

	if(maze->getCurrentRoom()->hasLeftRoom())
	{
		for(auto&e : maze->getCurrentRoom()->getCharacters())
			e->desassignCM();
		maze->Go(maze->getCurrentRoom()->nextRoomDirection());
		maze->getCurrentRoom()->assignCM(cm);

		for(auto& e : heroes)
		{
			e->setPosition(400,400);
			maze->getCurrentRoom()->addCharacter(e);
		}
	}
		
}