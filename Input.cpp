/* Implementation file of the input class
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Input.h"

Input::GameInput::GameInput(/*const sf::Input& _in*/) : /*joyInput(_in),*/posX(0),posY(0),relX(0),relY(0),up(sf::Keyboard::Key::Z),down(sf::Keyboard::Key::S),right(sf::Keyboard::Key::D),left(sf::Keyboard::Key::Q),shoot(sf::Keyboard::Key::Space),joyButtons(std::vector<bool>(15)),mode(Input::MouseKeyboard),shootJoy(0),upJoy(false),downJoy(false),rightJoy(false),leftJoy(false),escapeJoy(7)
{}

void Input::GameInput::update(std::vector<sf::Event> events)
{
  for (std::vector<sf::Event>::iterator ite = events.begin(); ite != events.end() ; ++ite)
	{
		 if (ite->type == sf::Event::KeyPressed)
		 {
			 clavier[ite->key.code] = true;
		 }

		 else if (ite->type == sf::Event::KeyReleased)
		 {
			 clavier[ite->key.code] = false;
		 }

		 else if (ite->type == sf::Event::MouseButtonPressed)
		 {
			 souris[(const char)ite->mouseButton.button] = true;
			 relX = posX - ite->mouseButton.x;
			 relY = posY - ite->mouseButton.y;
			 posX = ite->mouseButton.x;
			 posY = ite->mouseButton.y;
		 }

		 else if (ite->type == sf::Event::MouseButtonReleased)
		 {
			 souris[(const char)ite->mouseButton.button] = false;
		 }

		 else if (ite->type == sf::Event::JoystickButtonPressed)
		 {
			 joyButtons.at(ite->joystickButton.button) = true;
		 }

		 else if(ite->type == sf::Event::JoystickButtonPressed)
		 {
			 joyButtons.at(ite->joystickButton.button) = false;
		 }

		 else if (ite->type == sf::Event::JoystickMoved)
		 {
			 leftJoy = false;
			 downJoy = false;
			 rightJoy = false;
			 upJoy = false;
			
			 if (ite->joystickMove.axis == sf::Joystick::X)/*(joyInput.GetJoystickAxis(0, sf::Joystick::X) < -25)*/
			 {
					leftJoy = true;
			 }
			 /*else if (joyInput.GetJoystickAxis(0, sf::Joystick::X)  > 25)
			 {
					rightJoy = true;
			 }*/
			 if (ite->joystickMove.axis == sf::Joystick::Y)/*(joyInput.GetJoystickAxis(0, sf::Joystick::Y)  > 25)*/
			 {
				 upJoy = true;
			 }
			/* else if(joyInput.GetJoystickAxis(0, sf::Joystick::Y)  < -25)
			 {
				downJoy = true;
			 }*/

				
		 }
	}
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

int Input::GameInput::getPosX()
{
	return posX;
}

int Input::GameInput::getPosY()
{
	return posY;
}

bool Input::GameInput::isUp()
{
	return ((mode == MouseKeyboard) && clavier[up]) || ((mode == Joystick) && upJoy);
}

bool Input::GameInput::isDown()
{
	return ((mode == MouseKeyboard) && clavier[down]) || (( mode == Joystick) && downJoy);
}
bool Input::GameInput::isRight()
{
	return ((mode == MouseKeyboard) && clavier[right]) || (( mode == Joystick) && rightJoy);
}

bool Input::GameInput::isLeft()
{
	return ((mode == MouseKeyboard) && clavier[left]) || (( mode == Joystick) && leftJoy);
}

bool Input::GameInput::isShoot()
{
	return ((mode == MouseKeyboard) && clavier[shoot]) || ((mode == Joystick) && joyButtons.at(shootJoy));
}

bool Input::GameInput::isQuit()
{
	return ((mode == MouseKeyboard) && clavier[sf::Keyboard::Key::Escape]) || ((mode == Joystick) && joyButtons.at(escapeJoy)) ;
}

bool Input::GameInput::isKeyDown(sf::Keyboard::Key _c)
{
	return clavier[_c];
}

void Input::GameInput::cutKey(sf::Keyboard::Key _c)
{
	clavier[_c] = false;
}


