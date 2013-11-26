/* Implementation file of the input class
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Input.h"
#include "../Misc/Constantes.h"

Input::GameInput::GameInput(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right) :
posX(0),
posY(0),
relX(0),
relY(0),
up(_up),
down(_down),
right(_right),
left(_left),
shoot(sf::Keyboard::Space),
joyButtons(std::vector<bool>(15)),
mode(MouseKeyboard),
shootJoy(0),
upJoy(false),
downJoy(false),
rightJoy(false),
leftJoy(false),
escapeJoy(7),
locked(false)
{
	clavier[up] = false;
	clavier[down] = false;
	clavier[right] = false;
	clavier[left] = false;
	clavier[shoot] = false;
	clavier[sf::Keyboard::Escape] = false;
}

Input::GameInput::GameInput() : 
GameInput(sf::Keyboard::Z,sf::Keyboard::S,sf::Keyboard::Q,sf::Keyboard::D)
{}

void Input::GameInput::ListenToMove(std::function<void(int,int)> a)
{
	moveFuncs.push_back(a);
}

void Input::GameInput::triggerMove(int x, int y)
{
	for(auto e : moveFuncs)
	{
		e(x,y);
	}
}

void Input::GameInput::update(const sf::Event& ite)
{
	 if(!locked && isJoystickEvent(ite.type) && mode == MouseKeyboard)
	 {
	 	mode = Joystick;
	 }
	 else if(!locked && isMouseKeyboardEvent(ite.type) && mode == Joystick)
	 {
	 	mode = MouseKeyboard;
	 }

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
		 if(isUp())
		 	triggerMove(0,-1);
		 if(isDown())
		 	triggerMove(0,1);
		 if(isRight())
		 	triggerMove(1,0);
		 if(isLeft())
		 	triggerMove(-1,0);
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
	if(locked)
		return;

	if (mode == MouseKeyboard)
	{
		mode = Joystick;
	}
	else
	{
		mode = MouseKeyboard;
	}
}

bool Input::GameInput::rebindUp(const sf::Keyboard::Key& e )
{
	if(mode == Joystick)
		return true;
	up = e;
	clavier[up] = false;
	return false;
}

void Input::GameInput::lockJoystick(unsigned int   joystickId)
{
	mode = Joystick;
	JoyId = joystickId;
	locked = true;
}

void Input::GameInput::lockKeyboard()
{
	mode = MouseKeyboard;
	locked = true;
}


bool Input::GameInput::isJoystickEvent(sf::Event::EventType t) const
{
	return t == sf::Event::JoystickButtonPressed 
		|| t == sf::Event::JoystickButtonReleased
		|| t == sf::Event::JoystickMoved 
		|| t == sf::Event::JoystickConnected;
}

bool Input::GameInput::isMouseKeyboardEvent(sf::Event::EventType t) const
{
	return t == sf::Event::KeyPressed
		|| t == sf::Event::KeyReleased
		|| t == sf::Event::MouseWheelMoved 
		|| t == sf::Event::MouseButtonPressed
		|| t == sf::Event::MouseButtonReleased;
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
	return ((mode == MouseKeyboard) && clavier.at(up)) || ((mode == Joystick) && upJoy);
}

bool Input::GameInput::isDown() const
{
	return ((mode == MouseKeyboard) && clavier.at(down)) || (( mode == Joystick) && downJoy);
}
bool Input::GameInput::isRight() const
{
	return ((mode == MouseKeyboard) && clavier.at(right)) || (( mode == Joystick) && rightJoy);
}

bool Input::GameInput::isLeft() const
{
	return ((mode == MouseKeyboard) && clavier.at(left)) || (( mode == Joystick) && leftJoy);
}

bool Input::GameInput::isShoot() 
{
	bool res = ((mode == MouseKeyboard) && clavier.at(shoot)) || ((mode == Joystick) && joyButtons.at(shootJoy));

	if(mode == MouseKeyboard) cutKey(shoot);
	else joyButtons.at(shoot) = false;

	return res;
}

bool Input::GameInput::isQuit() const
{
	return ((mode == MouseKeyboard) && clavier.at(sf::Keyboard::Escape)) || ((mode == Joystick) && joyButtons.at(escapeJoy)) ;
}

bool Input::GameInput::isKeyDown(sf::Keyboard::Key _c) const
{
	return clavier.at(_c);
}

void Input::GameInput::cutKey(sf::Keyboard::Key _c)
{
	clavier[_c] = false;
}

Input::Input::Input(sf::RenderWindow& sc) :
	screen(sc),
	done(false)
{}

Input::Input::~Input()
{
	done = true;
}

const Input::GameInput& Input::Input::getGameInput() const
{
	return g_in;
}


