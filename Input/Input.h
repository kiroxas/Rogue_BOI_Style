/* Input.h
  File that take care of the Game Input, such as Keyboard, mouse and Joysticks.
  Author : Guillaume Mouton (Kiroxas)
*/

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <functional>

namespace Input
{

  enum InputType
	{
		MouseKeyboard,
		Joystick
	};

	class GameInput
	{
	public :
		GameInput(/*const sf::Input&*/);
		void update(sf::Event);
		int getPosX() const;
		int getPosY() const;
		bool isUp() const;
		bool isDown() const;
		bool isRight() const;
		bool isLeft() const;
		bool isShoot() const;
		bool isQuit() const;
		bool isKeyDown(sf::Keyboard::Key) const;
		void cutKey(sf::Keyboard::Key);

		void switchMode();
		void ListenToMove(std::function<void(int,int)>);

	private :

		void triggerMove(int x, int y);
		void clearAll();
		GameInput& operator =(const GameInput&);

		std::map<sf::Keyboard::Key, bool> clavier; 
		std::map<char, bool> souris;
		std::vector<bool> joyButtons;
		int posX, posY, relX, relY;
		InputType mode;
		std::vector<std::function<void(int,int)>> moveFuncs;

		sf::Keyboard::Key up;
		sf::Keyboard::Key down;
		sf::Keyboard::Key right;
		sf::Keyboard::Key left;
		sf::Keyboard::Key shoot;

		/*const sf::Input& joyInput;*/

		bool upJoy;
		bool downJoy;
		bool rightJoy;
		bool leftJoy;
		int shootJoy;
		int escapeJoy;
	};

	class Input
	{
	public :
		Input(sf::RenderWindow&);
		~Input();
		const GameInput& getGameInput() const;
	private :
		sf::RenderWindow& screen;
		GameInput g_in;
		bool done;
		//std::thread th;
	};
}


#endif
