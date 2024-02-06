#include "State.h"

State::State(sf::RenderWindow* window) :
	window(window)
{
}

State::~State()
{
}

const bool State::getQuit() const
{
	return quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		quit = true;
}
