#include "GameState.h"
#include <iostream>

GameState::GameState(sf::RenderWindow* window) :
	State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{

}

void GameState::updateKeyBinds(const float& deltaTime)
{
	checkForQuit();
}

void GameState::update(const float& deltaTime)
{
	updateKeyBinds(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
}
