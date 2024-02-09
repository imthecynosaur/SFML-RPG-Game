#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState :
	public State
{
	sf::Texture backGround;
	sf::Sprite BGSprite;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	void initializeFonts();
	void initializeKeyBinds();
	void initializeButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

