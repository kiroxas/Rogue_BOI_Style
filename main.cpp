/* Main file of the rogue project
   We will handle the main loop of the game here
   Author : Guillaume Mouton (Kiroxas)
*/

/* User defined includes */
#include "Maze/AbstractMazeGenerator.h"
#include "Maze/NormalMazeGenerator.h"
#include "Rendering Engine/Rendering.h"
#include "Input/Input.h"
#include "Misc/ImagePool.h"
#include "Characters/Character.h"

/* SFML includes */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/* STL includes */
#include <memory>
#include <time.h>
#include <stdlib.h>
#include <iostream>


int main()
{
	srand ( time(NULL) );
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator());
	std::unique_ptr<Maze> maze(g->CreateMaze(5));

	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style");
	window.setFramerateLimit(60);

	Input::Input in(window);
	Input::GameInput g_i;
	sf::Event event; 
	ImagePool p;

	Character hero(p.getImage("isaac"));
	auto func = std::bind(&Character::Move, &hero, std::placeholders::_1, std::placeholders::_2);
	g_i.ListenToMove(func);
	sf::Clock clock;

	for(;;)
	{
		window.clear();
		window.pollEvent(event);
		g_i.update(event);
		if(g_i.isShoot()) hero.stopAnimation();
		if(g_i.isQuit()) return 0;

		rendering::render_level(maze.get(),window);

		window.draw(hero);
		window.display();
		clock.restart();
	}
}
