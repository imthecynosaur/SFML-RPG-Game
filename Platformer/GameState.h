#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"


class GameState :
	public State
{
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	PauseMenu pauseMenu;
	Player* player;

	TileMap* tileMap;

	void initializeView();
	void initializeKeyBinds();
	void initializeTextures();
	void initializePlayers();
	void initialzeTileMap();

public:
	GameState(StateData* stateData);
	virtual ~GameState();

	void updateView(const float& deltaTime);
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

