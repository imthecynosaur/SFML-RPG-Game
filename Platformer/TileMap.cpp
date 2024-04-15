#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height) :
	gridSizef{gridSize}, maxSize {width, height}
{
	map.resize(maxSize.x);
	for (size_t x{ 0 }; x < maxSize.x; x++) {

		map.push_back(std::vector<std::vector<Tile*>>());
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			map[x].resize(maxSize.y);
			map[x].push_back(std::vector<Tile*>());
			for (size_t z{ 0 }; z < layers; z++) {
				map[x][y].resize(layers);
				map[x][y].push_back(nullptr);
			}
		}

	}

}

TileMap::~TileMap()
{
	for (size_t x{ 0 }; x < maxSize.x; x++) {
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			for (size_t z{ 0 }; z < layers; z++) {
				delete map[x][y][z];
				map[x][y][z] = nullptr;
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
			for (auto* z : y) {
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x >= 0 && y >= 0 && z >= 0 &&  x < maxSize.x && y < maxSize.y && z < layers) { 
		if (map[x][y][z] == nullptr) {
			map[x][y][z] = new Tile(x * gridSizef, y * gridSizef, gridSizef);
		}
	}
}

void TileMap::removeTile()
{
}


