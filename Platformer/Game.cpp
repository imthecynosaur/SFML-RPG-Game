#include "stdafx.h"
#include "Game.h"

void Game::initializeWindow()
{
	std::ifstream ifstream("Config/window.ini");
	videoModes = sf::VideoMode::getFullscreenModes();

	std::string title { "None" };
	sf::VideoMode windowBounds{ sf::VideoMode::getDesktopMode() };
	unsigned frameRateLimit{ 144 };
	bool verticalSyncEnabled{ false };
	unsigned antialiasingLevel{ 0 };

	if (ifstream.is_open()) {
		std::getline(ifstream, title);
		ifstream >> windowBounds.width >> windowBounds.height;
		ifstream >> fullScreen;
		ifstream >> frameRateLimit;
		ifstream >> verticalSyncEnabled;
		ifstream >> antialiasingLevel;
	}

	ifstream.close();

	contextSettings.antialiasingLevel = antialiasingLevel;
	if (fullScreen)
		window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen, contextSettings);
	else
		window = new sf::RenderWindow(windowBounds, title, sf::Style::Titlebar | sf::Style::Close, contextSettings);
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
	states.push(new MainMenuState(window, &supportedKeys, &states));
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
