#pragma once
#include "State.h"

class MainMenuState :
	public State
{
	sf::Texture backGround;
	sf::Sprite BGSprite;

	std::map<std::string, gui::Button*> buttons;

	void initializeKeyBinds();
	void initializeButtons();

public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

