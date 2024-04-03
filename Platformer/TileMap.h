#pragma once
#include "Tile.h"
class TileMap
{
private:
	float gridSizef{ 50.f };
	unsigned gridSizeU{ static_cast<unsigned>(gridSizef)};
	unsigned layers{ 1 };
	sf::Vector2u maxSize{ 10, 10 };
	std::vector<std::vector<std::vector<Tile>>> map;

public:
	TileMap();


	void update();
	void render(sf::RenderTarget& target);
};

