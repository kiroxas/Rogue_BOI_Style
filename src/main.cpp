/* Main file of the rogue project
   We will handle the main loop of the game here
   Author : Guillaume Mouton (Kiroxas)
*/

/* User defined includes */
#include "Rendering Engine/Rendering.h"
#include "Input/Input.h"
#include "Misc/ImagePool.h"
#include "Misc/GameInfo.h"
#include "Level.h"

/* SFML includes */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/* STL includes */
#include <memory>
#include <random>
#include <thread>
#include <chrono>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
	/* Creation of the window */
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rogue BOI Style",sf::Style::Resize);
	window.setFramerateLimit(60);

	GameInfo stats;
	ImagePool pool;
	std::vector<std::function<void()>> callbacks;
	
	/*sf::Music music;

	if(!music.openFromFile("../data/Music/01.flac"))
		return 1;
	music.play();*/

	/* Creation of the maze */

	Input::GameInput g_i(sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right);

	bool running = true;

	sf::Event event;
	sf::Clock clock;

	Level l(pool,g_i);

	g_i.Suscribe(Events::Quit(),[&running](){running = false;});
	callbacks.emplace_back(std::bind(&Input::GameInput::update,std::ref(g_i),std::ref(event)));
	callbacks.emplace_back(std::bind(&Level::update, std::ref(l)));

	while(running)
	{
			
			window.pollEvent(event);
			for(auto& e : callbacks)
				e();

			rendering::render_level(l,window,stats);
			window.display();
			stats.setFps(1.0f / clock.restart().asSeconds());
	}
}
