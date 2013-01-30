#include "NormalMazeGenerator.h"
#include "Constantes.h"


NormalMazeGenerator::NormalMazeGenerator(unsigned int number) :
	level_number(number)
{}

std::unique_ptr<Maze> NormalMazeGenerator::CreateMaze()
{

	infos::log(MAZE_LOG_PATH,"Generating Maze from NormalMaze");

	std::unique_ptr<Maze> g(new Maze(NUMBER_OF_ROOMS + 2*level_number));
	g->GenerateGraphStructure();

	return g;
}
