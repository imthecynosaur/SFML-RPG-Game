#pragma once
#include "State.h"
class GameState :
	public State
{
	Player* player;
	void initializeKeyBinds();
	void initializePlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

