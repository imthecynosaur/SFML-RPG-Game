#include <iostream>
#include "Game.h"

void Game::initializeWindow()
{
	std::ifstream ifstream("Config/window.ini");

	std::string title { "None" };
	sf::VideoMode windowBounds(800, 600);
	unsigned frameRateLimit = 144;
	bool verticalSyncEnabled = false;

	if (ifstream.is_open()) {
		std::getline(ifstream, title);
		ifstream >> windowBounds.width >> windowBounds.height;
		ifstream >> frameRateLimit;
		ifstream >> verticalSyncEnabled;
	}

	ifstream.close();

	window = new sf::RenderWindow(windowBounds, title);
	window->setFramerateLimit(frameRateLimit);
	window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::initializeKeys()
{
	std::ifstream ifstream("Config/supported_keys.ini");
	if (ifstream.is_open()) {
		std::string key { "" };
		int keyValue{};
		while (ifstream >> key >> keyValue) {
			supportedKeys[key] = keyValue;
		}
	}
	ifstream.close();
}

void Game::initializeStates()
{
	states.push(new MainMenuState(window, &supportedKeys));
	states.push(new GameState(window, &supportedKeys));
}

Game::Game()
{
	initializeKeys();
	initializeWindow();
	initializeStates();
}

Game::~Game()
{
	delete window;
	window = nullptr;

	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

void Game::endApplication()
{
}

void Game::updateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update()
{
	updateSFMLEvents();

	if (!states.empty()) {
		states.top()->update(deltaTime);

		if (states.top()->getQuit()) {
			states.top()->endState();
			delete states.top();
			states.pop();
		}
		
	}
	else {
		endApplication();
		window->close();
	}

}

void Game::render()
{
	window->clear();

	if (!states.empty())
		states.top()->render(window);

	window->display();
}

void Game::run()
{
	while (window->isOpen()) {
		updateDeltaTime();
		update();
		render();
	}
}
