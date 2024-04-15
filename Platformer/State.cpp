#include "stdafx.h"
#include "State.h"

void State::initializeFonts()
{
	if (!font.loadFromFile("Fonts/AGENCYR.TTF"))
		throw("ERROR::COULD NOT LOAD FONT");
}

State::State(StateData* stateData) : 
	stateData(stateData),window(stateData->window),supportedKeys(stateData->supportedKeys),
	states(stateData->states), gridSize(stateData->gridSize)
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
	mousePosGrid = sf::Vector2u(static_cast<unsigned>(mousePosView.x) / static_cast<unsigned>(gridSize),
													static_cast<unsigned>(mousePosView.y) / static_cast<unsigned>(gridSize));
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
