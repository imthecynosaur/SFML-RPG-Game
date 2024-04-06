#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"


class GameState :
	public State
{
	PauseMenu pauseMenu;
	Player* player;

	TileMap map;

	void initializeKeyBinds();
	void initializeTextures();
	void initializePlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

