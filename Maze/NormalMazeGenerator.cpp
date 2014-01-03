#include "NormalMazeGenerator.h"
#include "../Misc/Constantes.h"


NormalMazeGenerator::NormalMazeGenerator(const ImagePool& p,CollisionManager& _c) :
pool(p),
c(_c)
{}

std::unique_ptr<Maze> NormalMazeGenerator::CreateMaze(unsigned int level_number)
{

	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2 * level_number,pool,c));
	g->GenerateGraphStructure();

	return g;
}
