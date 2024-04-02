#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	map.resize(maxSize.x);
	for (size_t x{ 0 }; x < maxSize.x; x++) {

		map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			map[x].resize(maxSize.y);
			map[x].push_back(std::vector<Tile>());
			for (size_t z{ 0 }; z < layers; z++) {
				map[x][y].resize(layers);
				map[x][y].push_back(Tile(x * gridSizef, y *gridSizef, gridSizef));
			}
		}

	}

}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : map) {
		for (auto& y : x) {
			for (auto& z : y) {
				z.render(target);
			}
		}
	}
}


