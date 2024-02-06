#pragma once
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class State
{
	std::vector<sf::Texture> textures;
	
public:
	State();
	virtual ~State();

	virtual void update() = 0;
	virtual void render() = 0;
};

