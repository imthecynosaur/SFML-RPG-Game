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

Game::Game()
{
	initializeWindow();
}

Game::~Game()
{
	delete window;
	window = nullptr;
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
}

void Game::render()
{
	window->clear();
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
