#pragma once
#include "State.h"

class SettingsState :
    public State
{
	sf::Texture backGround;
	sf::Sprite BGSprite;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDowns;

	sf::Text optionsText;
	std::vector<sf::VideoMode> videoModes;

	void initializeKeyBinds();
	void initializeGui();
	void initializeText();

public:
	SettingsState(StateData* stateData);
	virtual ~SettingsState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateGui(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
	void renderGui(sf::RenderTarget* target);
};

