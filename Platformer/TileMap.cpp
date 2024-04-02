#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	for (size_t x{ 0 }; x < maxSize.x; x++) {
		map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			map[x].push_back(std::vector<Tile>());
			for (size_t z{ 0 }; z < layers; z++) {
				map[x][y].push_back(Tile());
			}
		}

	}

}
