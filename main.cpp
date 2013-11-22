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
#include <random>


int main()
{
	/* Creation of the window */
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style",sf::Style::Resize);
	window.setFramerateLimit(60);

	ImagePool pool;

	/* Creation of the maze */
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(pool));
	std::unique_ptr<Maze> maze(g->CreateMaze(5));

	Input::GameInput g_i;
	Input::GameInput g_i2(sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right);

	std::vector<std::unique_ptr<Character>> characters;
	characters.emplace_back(new Character(pool.getImage("isaac")));
	characters.emplace_back(new Character(pool.getImage("fire")));
	
	auto func = std::bind(&Character::Move, characters[0].get(), std::placeholders::_1, std::placeholders::_2);
	//auto func2 = std::bind(&Character::Move, characters[1].get(), std::placeholders::_1, std::placeholders::_2);
	g_i.ListenToMove(func);
	//g_i2.ListenToMove(func2);

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> int_distribution(0,10);

	sf::Event event; 
	bool running = true;
	std::vector<std::function<void()>> callbacks;
	callbacks.emplace_back(std::bind(&Input::GameInput::update,std::ref(g_i),std::ref(event)));
	callbacks.emplace_back(std::bind(&Input::GameInput::update,std::ref(g_i2),std::ref(event)));
	callbacks.emplace_back(std::bind(&Character::animate,characters[1].get()));
	callbacks.emplace_back([&](){if(g_i.isShoot()) maze = g->CreateMaze(int_distribution(generator));});
	callbacks.emplace_back([&](){if(g_i.isQuit()) running = false;});

	while(running)
	{
		window.pollEvent(event);
		for(auto& e : callbacks)
			e();

		window.clear();
		rendering::render_level(characters,maze.get(),window);
		window.display();
	}
}
