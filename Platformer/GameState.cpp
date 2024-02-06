#include "GameState.h"
#include <iostream>

void GameState::initializeKeyBinds()
{
	keybinds.emplace("MOVE_LEFT", supportedKeys->at("A"));
	keybinds.emplace("MOVE_RIGHT", supportedKeys->at("D"));
	keybinds.emplace("MOVE_UP", supportedKeys->at("W"));
	keybinds.emplace("MOVE_DOWN", supportedKeys->at("S"));
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) :
	State(window, supportedKeys)
{
	initializeKeyBinds();
}

GameState::~GameState()
{
}

void GameState::endState()
{

}

void GameState::updateInput(const float& deltaTime)
{
	checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player.move(deltaTime, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player.move(deltaTime, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player.move(deltaTime, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player.move(deltaTime, 0.f, 1.f);
}

void GameState::update(const float& deltaTime)
{
	updateInput(deltaTime);
	player.update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	player.render(target);
}
