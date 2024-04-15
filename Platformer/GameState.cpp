#include "stdafx.h"
#include "GameState.h"


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

void GameState::initialzeTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 10, 10);
}

GameState::GameState(StateData* stateData) :
	State(stateData), pauseMenu(*window, font)
{
	initializeKeyBinds();
	initializeTextures();
	initializePlayers();
	initialzeTileMap();
}

GameState::~GameState()
{
	delete player;
	player = nullptr;

	delete tileMap;
	tileMap = nullptr;
}

void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyCooldown()) {
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
	
}

void GameState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(1.f, 0.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0.f, -1.f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0.f, 1.f, deltaTime);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		player->attack(deltaTime);

	
}

void GameState::update(const float& deltaTime)
{
	updateMousePositions();
	updateKeyLastPressed(deltaTime);
	updateInput(deltaTime);

	if (!paused) {
		updatePlayerInput(deltaTime);
		player->update(deltaTime);
	}
	else {
		pauseMenu.update(mousePosView);
		if (pauseMenu.isButtonPressed("Quit"))
			endState();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	
	//map.render(*target);
	player->render(*target);

	if (paused) {
		pauseMenu.render(*target);
	}
}
