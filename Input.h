/* Input.h
  File that take care of the Game Input, such as Keyboard, mouse and Joysticks.
  Author : Guillaume Mouton (Kiroxas)
*/

#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include <map>

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
		void update(std::vector<sf::Event>);
		int getPosX();
		int getPosY();
		bool isUp();
		bool isDown();
		bool isRight();
		bool isLeft();
		bool isShoot();
		bool isQuit();
		bool isKeyDown(sf::Keyboard::Key);
		void cutKey(sf::Keyboard::Key);

		void switchMode();

	private :

		void clearAll();
		GameInput& operator =(const GameInput&);

		std::map<sf::Keyboard::Key, bool> clavier; 
		std::map<char, bool> souris;
		std::vector<bool> joyButtons;
		int posX, posY, relX, relY;
		Input::InputType mode;

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
}


#endif
