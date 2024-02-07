#pragma once
#include "Entity.h"
#include "Button.h"

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit{ false };

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	std::vector<sf::Texture> textures;

	virtual void initializeKeyBinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool getQuit() const;
	virtual void  checkForQuit();

	virtual void updateMousePositions();
	
	virtual void endState() = 0;
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};