#pragma once
#include "Tile.h"
class TileMap
{
private:
	float gridSizef{ };
	unsigned gridSizeU{ static_cast<unsigned>(gridSizef)};
	unsigned layers{ 1 };
	sf::Vector2u maxSize{};
	std::vector<std::vector<std::vector<Tile*>>> map{};
	sf::Texture tilesTexture{};

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

