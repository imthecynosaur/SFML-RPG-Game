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

void GameState::initializeTextures()
{
	if (! textures["countessVampire"].loadFromFile("Assets/countess_vampire/Countess_Vampire_Spritelist.png"))
		std::cout << "didn't load countess vampire sprite sheet" << std::endl;
}

void GameState::initializePlayers()
{
	player = new Player(200, 800, textures["countessVampire"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeKeyBinds();
	initializeTextures();
	initializePlayers();
}

GameState::~GameState()
{
	delete player;
	player = nullptr;
}

void GameState::updateInput(const float& deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0.f, -1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0.f, 1.f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE")))) {
		endState();
	}
}

void GameState::update(const float& deltaTime)
{
	updateMousePositions();
	updateInput(deltaTime);
	player->update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	player->render(target);
}
