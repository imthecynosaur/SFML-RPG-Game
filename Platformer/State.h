#pragma once
#include "Entity.h"

class State
{
protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit{ false };
	
	std::vector<sf::Texture> textures;

	virtual void initializeKeyBinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool getQuit() const;
	virtual void  checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};