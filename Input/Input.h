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
#include "../Misc/Suscribable.h"

namespace Input
{

  enum InputType
	{
		MouseKeyboard,
		Joystick
	};

	class GameInput : public Suscribable<Events::Shoot,void>, 
					  public Suscribable<Events::Quit,void>, 
	                  public Suscribable<Events::Move, std::pair<int,int>> 
	{
	public :

	using Suscribable<Events::Shoot,void>::Suscribe;
    using Suscribable<Events::Move, std::pair<int,int>>::Suscribe;
    using Suscribable<Events::Quit,void>::Suscribe;

    using Suscribable<Events::Shoot,void>::Notify;
    using Suscribable<Events::Move, std::pair<int,int>>::Notify;
    using Suscribable<Events::Quit,void>::Notify;

		GameInput(/*const sf::Input&*/);
		GameInput(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
		void update(const sf::Event&);
		int getPosX() const;
		int getPosY() const;
		bool isUp() const;
		bool isDown() const;
		bool isRight() const;
		bool isLeft() const;
		bool isShoot();
		bool isQuit() const;
		bool isKeyDown(sf::Keyboard::Key) const;
		void cutKey(sf::Keyboard::Key);
		void lockJoystick(unsigned int joystickId);
		void lockKeyboard();

		void switchMode();
		bool rebindUp(const sf::Keyboard::Key&);

	private :

		void clearAll();
		GameInput& operator =(const GameInput&);
		bool isJoystickEvent(sf::Event::EventType) const;
		bool isMouseKeyboardEvent(sf::Event::EventType) const;

		std::map<sf::Keyboard::Key, bool> clavier; 
		std::map<char, bool> souris;
		std::map<unsigned int,bool> joyButtons;
		int posX, posY, relX, relY;
		InputType mode;

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

		unsigned int JoyId;
		bool locked;
	};
};
#endif
