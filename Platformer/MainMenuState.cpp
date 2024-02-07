#include "MainMenuState.h"

void MainMenuState::initializeKeyBinds()
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

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) :
	State(window, supportedKeys)
{
	initializeKeyBinds();
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::endState()
{

}

void MainMenuState::updateInput(const float& deltaTime)
{
	checkForQuit();
}

void MainMenuState::update(const float& deltaTime)
{
	updateInput(deltaTime);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(background);
}

