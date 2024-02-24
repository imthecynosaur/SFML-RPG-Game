#pragma once
#include "State.h"
#include "Button.h"
class EditorState :
    public State
{
	sf::Font font;

	std::map<std::string, Button*> buttons;

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

