#pragma once
#include "GameState.h"
class MainMenuState :
	public State
{
	sf::RectangleShape background;

	void initializeKeyBinds();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	void endState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

