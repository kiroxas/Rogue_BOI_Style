/* Implementation file of the input class
   Author : Guillaume Mouton (Kiroxas)
*/

#include "Input.h"

GameInput::Input(const sf::Input& _in) : joyInput(_in),posX(0),posY(0),relX(0),relY(0),up(sf::Key::Z),down(sf::Key::S),right(sf::Key::D),left(sf::Key::Q),jump(sf::Key::Space),joyButtons(std::vector<bool>(15)),mode(clavierSouris),jumpJoy(0),upJoy(false),downJoy(false),rightJoy(false),leftJoy(false),escapeJoy(7)
{}

void GameInput::update(std::vector<sf::Event> events)
{
  for (std::vector<sf::Event>::iterator ite = events.begin(); ite != events.end() ; ++ite)
	{
		 if (ite->Type == sf::Event::KeyPressed)
		 {
			 clavier[ite->Key.Code] = true;
		 }

		 else if (ite->Type == sf::Event::KeyReleased)
		 {
			 clavier[ite->Key.Code] = false;
		 }

		 else if (ite->Type == sf::Event::MouseButtonPressed)
		 {
			 souris[(const char)ite->MouseButton.Button] = true;
			 relX = posX - ite->MouseButton.X;
			 relY = posY - ite->MouseButton.Y;
			 posX = ite->MouseButton.X;
			 posY = ite->MouseButton.Y;
		 }

		 else if (ite->Type == sf::Event::MouseButtonReleased)
		 {
			 souris[(const char)ite->MouseButton.Button] = false;
		 }

		 else if (ite->Type == sf::Event::JoyButtonPressed)
		 {
			 joyButtons.at(ite->JoyButton.Button) = true;
		 }

		 else if(ite->Type == sf::Event::JoyButtonReleased)
		 {
			 joyButtons.at(ite->JoyButton.Button) = false;
		 }

		 else if (ite->Type == sf::Event::JoyMoved)
		 {
			 leftJoy = false;
			 downJoy = false;
			 rightJoy = false;
			 upJoy = false;
			
			 if (joyInput.GetJoystickAxis(0, sf::Joy::AxisX) < -25)
			 {
					leftJoy = true;
			 }
			 else if (joyInput.GetJoystickAxis(0, sf::Joy::AxisX)  > 25)
			 {
					rightJoy = true;
			 }
			 if (joyInput.GetJoystickAxis(0, sf::Joy::AxisY)  > 25)
			 {
				 upJoy = true;
			 }
			 else if(joyInput.GetJoystickAxis(0, sf::Joy::AxisY)  < -25)
			 {
				downJoy = true;
			 }

				
		 }
	}
}

void GameInput::clearAll()
{
	for (std::map<sf::Key::Code, bool>::iterator ite = clavier.begin(); ite != clavier.end(); ++ite)
	{
		ite->second = false;
	}

	for (std::map<char, bool>::iterator ite = souris.begin(); ite != souris.end(); ++ite)
	{
		ite->second = false;
	}
}

void GameInput::switchMode()
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

int GameInput::getPosX()
{
	return posX;
}

int GameInput::getPosY()
{
	return posY;
}

bool GameInput::isUp()
{
	return ((mode == MouseKeyboard) && clavier[up]) || ((mode == Joystick) && upJoy);
}

bool GameInput::isDown()
{
	return ((mode == MouseKeyboard) && clavier[down]) || (( mode == Joystick) && downJoy);
}
bool GameInput::isRight()
{
	return ((mode == MouseKeyboard) && clavier[right]) || (( mode == Joystick) && rightJoy);
}

bool GameInput::isLeft()
{
	return ((mode == MouseKeyboard) && clavier[left]) || (( mode == Joystick) && leftJoy);
}

bool GameInput::isShoot()
{
	return ((mode == MouseKeyboard) && clavier[jump]) || ((mode == Joystick) && joyButtons.at(shootJoy));
}

bool GameInput::isQuit()
{
	return ((mode == MouseKeyboard) && clavier[sf::Key::Escape]) || ((mode == Joystick) && joyButtons.at(escapeJoy)) ;
}

bool GameInput::isKeyDown(sf::Key::Code _c)
{
	return clavier[_c];
}

void GameInput::cutKey(sf::Key::Code _c)
{
	clavier[_c] = false;
}


