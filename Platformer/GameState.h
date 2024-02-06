#pragma once
#include "State.h"
class GameState :
	public State
{
	Entity player;

	void initializeKeyBinds();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	void endState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

