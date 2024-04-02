#pragma once
#include "Tile.h"
class TileMap
{
private:
	unsigned gridSizeU{ 50 }; 
	unsigned layers{ 5 };
	sf::Vector2u maxSize{ 5000, 5000 };
	std::vector<std::vector<std::vector<Tile>>> map;

public:
	TileMap();
};

