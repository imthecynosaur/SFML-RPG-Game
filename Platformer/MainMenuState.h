#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "GraphicsSettings.h"
class MainMenuState :
	public State
{
	GraphicsSettings& gfxSettings;
	sf::Texture backGround;
	sf::Sprite BGSprite;

	std::map<std::string, gui::Button*> buttons;

	void initializeKeyBinds();
	void initializeButtons();

public:
	MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings,
		std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

