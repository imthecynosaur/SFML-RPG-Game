#pragma once
#include "State.h"
class GameState :
	public State
{

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void endState();


	void updateKeyBinds(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

