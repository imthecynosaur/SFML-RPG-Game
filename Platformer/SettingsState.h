#pragma once
#include "State.h"
class SettingsState :
    public State
{
	sf::Texture backGround;
	sf::Sprite BGSprite;

	std::map<std::string, Button*> buttons;

	void initializeKeyBinds();
	void initializeButtons();

public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

