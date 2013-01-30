#include "AbstractMazeGenerator.h"
#include "DrunkMazeGenerator.h"
#include "NormalMazeGenerator.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Rendering.h"

#include <memory>
#include <time.h>
#include <stdlib.h>

int main()
{
	srand ( time(NULL) );
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(3));
	std::unique_ptr<Maze> maze(g->CreateMaze());

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	rendering::render_map(maze.get(),window,std::make_pair(0,0),std::make_pair(800,600));

	//sf::Shape Polygon;
	//Polygon.AddPoint(0, 0,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	//Polygon.AddPoint(0, 100,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	//Polygon.AddPoint(100, 100,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));
	//Polygon.AddPoint(100, 0,  sf::Color(255, 0, 0),     sf::Color(0, 128, 128));

	//App.Draw(Polygon);

	system("pause");
}