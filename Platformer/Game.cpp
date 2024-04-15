#include "stdafx.h"
#include "Game.h"

void Game::initializeGraphicsSettings()
{
	gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initializeWindow()
{
	if (gfxSettings.fullScreen)
		window = new sf::RenderWindow(gfxSettings.resolution,
			gfxSettings.title, sf::Style::Fullscreen, gfxSettings.contextSettings);
	else
		window = new sf::RenderWindow(gfxSettings.resolution,
			gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, gfxSettings.contextSettings);
	window->setFramerateLimit(gfxSettings.frameRateLimit);
	window->setVerticalSyncEnabled(gfxSettings.verticalSync);
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

void Game::initializeStateData()
{
	stateData.window = window;
	stateData.gfxSettings = &gfxSettings;
	stateData.supportedKeys = &supportedKeys;
	stateData.states = &states;
	stateData.gridSize = gridSize;
}

void Game::initializeStates()
{
	states.push(new MainMenuState(&stateData));
}

Game::Game()
{
	initializeGraphicsSettings();
	initializeKeys();
	initializeWindow();
	initializeStateData();
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
