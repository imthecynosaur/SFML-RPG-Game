#include "GameState.h"
#include <iostream>

void GameState::initializeKeyBinds()
{
	std::ifstream ifstream("Config/gamestate_keybinds.ini");
	if (ifstream.is_open()) {
		std::string command{ "" };
		std::string key{ "" };
		while (ifstream >> command >> key)
			keybinds[command] = supportedKeys->at(key);
	}
	ifstream.close();
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
