/* Implementation file of the input class
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Input.h"
#include <future>

Input::GameInput::GameInput(/*const sf::Input& _in*/) : /*joyInput(_in),*/posX(0),posY(0),relX(0),relY(0),up(sf::Keyboard::Key::Z),down(sf::Keyboard::Key::S),right(sf::Keyboard::Key::D),left(sf::Keyboard::Key::Q),shoot(sf::Keyboard::Key::Space),joyButtons(std::vector<bool>(15)),mode(InputType::MouseKeyboard),shootJoy(0),upJoy(false),downJoy(false),rightJoy(false),leftJoy(false),escapeJoy(7)
{
	clavier[up] = false;
	clavier[down] = false;
	clavier[right] = false;
	clavier[left] = false;
	clavier[shoot] = false;
	clavier[sf::Keyboard::Key::Escape] = false;
}

void Input::GameInput::update(sf::Event ite)
{
	lock_input.lock();
	 if (ite.type == sf::Event::KeyPressed)
	 {
		 clavier[ite.key.code] = true;
		}

		 else if (ite.type == sf::Event::KeyReleased)
		 {
			 clavier[ite.key.code] = false;
		 }

		 else if (ite.type == sf::Event::MouseButtonPressed)
		 {
			 souris[(const char)ite.mouseButton.button] = true;
			 relX = posX - ite.mouseButton.x;
			 relY = posY - ite.mouseButton.y;
			 posX = ite.mouseButton.x;
			 posY = ite.mouseButton.y;
		 }

		 else if (ite.type == sf::Event::MouseButtonReleased)
		 {
			 souris[(const char)ite.mouseButton.button] = false;
		 }

		 else if (ite.type == sf::Event::JoystickButtonPressed)
		 {
			 joyButtons.at(ite.joystickButton.button) = true;
		 }

		 else if(ite.type == sf::Event::JoystickButtonPressed)
		 {
			 joyButtons.at(ite.joystickButton.button) = false;
		 }

		 else if (ite.type == sf::Event::JoystickMoved)
		 {
			 leftJoy = false;
			 downJoy = false;
			 rightJoy = false;
			 upJoy = false;
			
			 if (ite.joystickMove.axis == sf::Joystick::X)/*(joyInput.GetJoystickAxis(0, sf::Joystick::X) < -25)*/
			 {
					leftJoy = true;
			 }
			 /*else if (joyInput.GetJoystickAxis(0, sf::Joystick::X)  > 25)
			 {
					rightJoy = true;
			 }*/
			 if (ite.joystickMove.axis == sf::Joystick::Y)/*(joyInput.GetJoystickAxis(0, sf::Joystick::Y)  > 25)*/
			 {
				 upJoy = true;
			 }
			/* else if(joyInput.GetJoystickAxis(0, sf::Joystick::Y)  < -25)
			 {
				downJoy = true;
			 }*/

				
		 }
		 lock_input.unlock();
}

void Input::GameInput::clearAll()
{
	for (std::map<sf::Keyboard::Key, bool>::iterator ite = clavier.begin(); ite != clavier.end(); ++ite)
	{
		ite->second = false;
	}

	for (std::map<char, bool>::iterator ite = souris.begin(); ite != souris.end(); ++ite)
	{
		ite->second = false;
	}
}

void Input::GameInput::switchMode()
{
	if (mode == MouseKeyboard)
	{
		mode = Joystick;
	}
	else
	{
		mode = MouseKeyboard;
	}
}

int Input::GameInput::getPosX() const
{
	return posX;
}

int Input::GameInput::getPosY() const
{
	return posY;
}

bool Input::GameInput::isUp() const
{
	lock_input.lock();
	bool res = ((mode == MouseKeyboard) && clavier.at(up)) || ((mode == Joystick) && upJoy);
	lock_input.unlock();
	return res;
}

bool Input::GameInput::isDown() const
{
	lock_input.lock();
	bool res =  ((mode == MouseKeyboard) && clavier.at(down)) || (( mode == Joystick) && downJoy);
	lock_input.unlock();
	return res;
}
bool Input::GameInput::isRight() const
{
	lock_input.lock();
	bool res =  ((mode == MouseKeyboard) && clavier.at(right)) || (( mode == Joystick) && rightJoy);
	lock_input.unlock();
	return res;
}

bool Input::GameInput::isLeft() const
{
	lock_input.lock();
	bool res =  ((mode == MouseKeyboard) && clavier.at(left)) || (( mode == Joystick) && leftJoy);
	lock_input.unlock();
	return res;
}

bool Input::GameInput::isShoot() const
{
	lock_input.lock();
	bool res =  ((mode == MouseKeyboard) && clavier.at(shoot)) || ((mode == Joystick) && joyButtons.at(shootJoy));
	lock_input.unlock();
	return res;
}

bool Input::GameInput::isQuit() const
{
	lock_input.lock();
	bool res =  ((mode == MouseKeyboard) && clavier.at(sf::Keyboard::Key::Escape)) || ((mode == Joystick) && joyButtons.at(escapeJoy)) ;
	lock_input.unlock();
	return res ;
}

bool Input::GameInput::isKeyDown(sf::Keyboard::Key _c) const
{
	return clavier.at(_c);
}

void Input::GameInput::cutKey(sf::Keyboard::Key _c)
{
	clavier[_c] = false;
}

#include <iostream>

Input::Input::Input(sf::RenderWindow& sc) :
	screen(sc),
	done(false),
	th([&]{  sf::Event event;  while(!done){ if (screen.pollEvent(event)) g_in.update(event); sf::sleep(sf::milliseconds(100));}})
{
	//std::async(std::launch::async,  });
}

Input::Input::~Input()
{
	done = true;
	th.join();
}

const Input::GameInput& Input::Input::getGameInput() const
{
	return g_in;
}


