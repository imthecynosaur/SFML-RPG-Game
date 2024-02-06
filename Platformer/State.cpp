#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) :
	window(window), supportedKeys(supportedKeys)
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
