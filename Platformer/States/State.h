#pragma once
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>

class State
{
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool quit{ false };
	
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool getQuit() const;
	virtual void  checkForQuit();
	
	virtual void endState() = 0;
	virtual void updateKeyBinds(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

