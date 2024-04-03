#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"


class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
	sf::Font font;
	PauseMenu pauseMenu;

	std::map<std::string, gui::Button*> buttons;
	
	TileMap map;

	void initializeFonts();
	void initializeKeyBinds();
	void initializeButtons();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState();

	void updateInput(const float& deltaTime);
	void update(const float& deltaTime);
	void updateButtons();
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

