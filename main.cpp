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
#include "Characters/Static_Entity.h"
#include "Characters/CollisionManager.h"

/* SFML includes */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/* STL includes */
#include <memory>
#include <random>
#include <thread>
#include <chrono>


int main()
{
	/* Creation of the window */
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style",sf::Style::Resize);
	window.setFramerateLimit(60);

	ImagePool pool;
	CollisionManager collision;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> int_distribution(0,10);

	/* Creation of the maze */
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(pool,collision));
	std::unique_ptr<Maze> maze(g->CreateMaze(int_distribution(generator)));

	Input::GameInput g_i(sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right);

	std::vector<std::unique_ptr<Character>> characters;
	characters.emplace_back(new Character(pool.getImage("isaac"),collision));
	characters.emplace_back(new Static_Entity(pool.getImage("fire"),collision));

	bool running = true;
	
	g_i.ListenToMove(std::bind(&Character::Move, characters[0].get(), std::placeholders::_1, std::placeholders::_2));
	g_i.ListenToShoot(std::bind(&Character::shoot, characters[0].get()));
	g_i.ListenToQuit([&running](){running = false;});

	sf::Event event; 
	
	std::vector<std::function<void()>> callbacks;
	callbacks.emplace_back(std::bind(&Input::GameInput::update,std::ref(g_i),std::ref(event)));
	callbacks.emplace_back(std::bind(&Character::animate,characters[1].get()));

	rendering::render_map(maze.get(),window,std::make_pair(0,0),std::make_pair(400,100));

	while(running)
	{
			window.pollEvent(event);
			for(auto& e : callbacks)
				e();

			rendering::render_level(characters,maze.get(),window);
			window.display();
	}
}
