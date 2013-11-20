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


int main()
{
	/* Creation of the window */
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style");
	window.setFramerateLimit(60);

	/* Creation of the maze */
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator());
	std::unique_ptr<Maze> maze(g->CreateMaze(5));

	ImagePool pool;

	Input::GameInput g_i;
	Input::GameInput g_i2(sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right);

	std::vector<std::unique_ptr<Character>> characters;
	characters.emplace_back(new Character(pool.getImage("isaac")));
	characters.emplace_back(new Character(pool.getImage("isaac")));
	
	auto func = std::bind(&Character::Move, characters[0].get(), std::placeholders::_1, std::placeholders::_2);
	auto func2 = std::bind(&Character::Move, characters[1].get(), std::placeholders::_1, std::placeholders::_2);
	g_i.ListenToMove(func);
	g_i2.ListenToMove(func2);

	sf::Event event; 
	bool running = true;

	while(running)
	{
		window.pollEvent(event);
		g_i.update(event);
		g_i2.update(event);

		if(g_i.isQuit()) running = false;

		window.clear();
		rendering::render_level(characters,maze.get(),window);
		window.display();
	}
}
