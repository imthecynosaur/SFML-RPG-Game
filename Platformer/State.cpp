#include "stdafx.h"
#include "State.h"

void State::initializeFonts()
{
	if (!font.loadFromFile("Fonts/AGENCYR.TTF"))
		throw("ERROR::COULD NOT LOAD FONT");
}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	window(window), supportedKeys(supportedKeys), states(states)
{
	initializeFonts();
}

State::~State()
{
}

const bool State::getQuit() const
{
	return quit;
}

void State::updateKeyLastPressed(const float& deltaTime)
{
	if (keyLastPressed < keyCooldown)
		keyLastPressed += 50.f * deltaTime;
}

const bool State::getKeyCooldown()
{
	if (keyLastPressed >= keyCooldown) {
		keyLastPressed = 0.f;
		return true;
	}
	return false;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

void State::endState()
{
	quit = true;
}
