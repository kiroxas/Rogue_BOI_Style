#ifndef REBIND_INPUTS_MENU
#define REBIND_INPUTS_MENU

#include <SFML/Graphics.hpp>
#include "../Input/Input.h"

class Rebind_Inputs_Menu
{
	public :
		Rebind_Inputs_Menu(sf::RenderTarget& target, Input::GameInput&);

	private :
	Input::GameInput& g_i;
	sf::RenderTarget& windows;
};

#endif