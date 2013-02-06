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
		GameInput(const sf::Input&);
		void update(std::vector<sf::Event>);
		int getPosX();
		int getPosY();
		bool isUp();
		bool isDown();
		bool isRight();
		bool isLeft();
		bool isShoot();
		bool isQuit();
		bool isKeyDown(sf::Key::Code);
		void cutKey(sf::Key::Code _c);

		void switchMode();

	private :

		void clearAll();
		Entree& operator =(const GameInput&);

		std::map<sf::Key::Code, bool> clavier; 
		std::map<char, bool> souris;
		std::vector<bool> joyButtons;
		int posX, posY, relX, relY;
		Input::InputType mode;

		sf::Key::Code up;
		sf::Key::Code down;
		sf::Key::Code right;
		sf::Key::Code left;
		sf::Key::Code shoot;

		const sf::Input& joyInput;

		bool upJoy;
		bool downJoy;
		bool rightJoy;
		bool leftJoy;
		int shootJoy;
		int escapeJoy;
	};
}


#endif
