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
#include "Characters/Ai.h"
#include "Misc/GameInfo.h"

/* SFML includes */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/* STL includes */
#include <memory>
#include <random>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>


int main()
{
	/* Creation of the window */
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style",sf::Style::Resize);
	window.setFramerateLimit(60);

	GameInfo stats;
	ImagePool pool;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> int_distribution(0,10);
	/*sf::Music music;

	if(!music.openFromFile("./data/Music/01.flac"))
		return 1;
	music.play();*/

	/* Creation of the maze */
	std::unique_ptr<AbstractMazeGenerator> g(new NormalMazeGenerator(pool));
	std::unique_ptr<Maze> maze(g->CreateMaze(int_distribution(generator)));

	Input::GameInput g_i(sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right);

	CollisionManager* collision = new CollisionManager();
	std::vector<std::unique_ptr<Character>> characters;
	std::vector<std::function<void()>> callbacks;

	maze->getCurrentRoom()->assignCM(collision);
	maze->getCurrentRoom()->registerCallbacks(callbacks);
	characters.emplace_back(new Character(pool.getImage("isaac"),collision));
	characters.emplace_back(new Character(pool.getImage("isaac"),collision));

	bool running = true;

	Ai ai; 
	
	g_i.ListenToMove(std::bind(&Character::Move, characters[0].get(), std::placeholders::_1, std::placeholders::_2));
	g_i.ListenToShoot(std::bind(&Character::shoot, characters[0].get()));
	ai.ListenToShoot(std::bind(&Character::shoot, characters[1].get()));
	ai.ListenToMove(std::bind(&Character::Move, characters[1].get(), std::placeholders::_1, std::placeholders::_2));
	g_i.ListenToQuit([&running](){running = false;});

	sf::Event event; 
	
	callbacks.emplace_back(std::bind(&Input::GameInput::update,std::ref(g_i),std::ref(event)));
	callbacks.emplace_back(std::bind(&Ai::update,std::ref(ai)));

	rendering::render_map(maze.get(),window,std::make_pair(0,0),std::make_pair(400,100));

	while(running)
	{
			window.pollEvent(event);
			for(auto& e : callbacks)
				e();

			rendering::render_level(characters,maze.get(),window,stats);
			window.display();
	}
}
