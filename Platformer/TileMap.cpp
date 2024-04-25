#include "stdafx.h"
#include "TileMap.h"
#include "format"

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string textureAddress) :
	gridSizef{ gridSize }, maxSize{ width, height }, textureAddress{textureAddress}
{
	map.resize(maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x{ 0 }; x < maxSize.x; x++) {
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			map[x].resize(maxSize.y, std::vector<Tile*>());
			for (size_t z{ 0 }; z < layers; z++) {
				map[x][y].resize(layers, nullptr);
			}
		}
	}
	if (!tileSheet.loadFromFile(textureAddress))
		std::cout << "couldn't load grass texture\n";
	
}

void TileMap::cleanUp()
{
	for (size_t x{ 0 }; x < maxSize.x; x++) {
		for (size_t y{ 0 }; y < maxSize.y; y++) {
			for (size_t z{ 0 }; z < layers; z++) {
				delete map[x][y][z];
				map[x][y][z] = nullptr;
			}
		}
	}
	map.clear();
}

TileMap::~TileMap()
{
	cleanUp();
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &tileSheet;
}


void TileMap::saveToFile(const std::string fileName)
{
	/*Saves the entire tilemap to a text-file
	* Format:
	* Basic:
	* Size x y
	* gridSize
	* layers
	* texture file
	* 
	* All tiles:
	* gridPos x y layer, Texture rect x y, collision, type
	*/

	std::ofstream ofStream;
	ofStream.open(fileName);

	if (ofStream.is_open()) {
		ofStream << maxSize.x << " " << maxSize.y << "\n"
			<< gridSizeU << "\n"
			<< layers << "\n"
			<< textureAddress << "\n";

		for (size_t x{ 0 }; x < maxSize.x; x++) {
			for (size_t y{ 0 }; y < maxSize.y; y++) {
				for (size_t z{ 0 }; z < layers; z++) {
					if (map[x][y][z]) {
						ofStream << x << " " << y << " " << z << " " << map[x][y][z]->getAsString() << " ";
					}
				}
			}
		}
	}
	else {
		std::cout << "Error::TileMap::Couldn't save to file, file name:" << fileName << '\n';
	}

	ofStream.close();
}



void TileMap::loadFromFile(const std::string fileName) 
{
	std::ifstream ifStream;
	ifStream.open(fileName);

	if (ifStream.is_open()) {
		ifStream >> maxSize.x >> maxSize.y >> gridSizeU >> layers;

		// IMPORTANT !!! THIS LINE CAN CAUSE BUGS IF THE TEXTURE ADDRESS DOESN'T CONTAIN WHITE SPACES!!
		std::getline(ifStream, textureAddress);
		// IMPORTANT !!! THIS LINE CAN CAUSE BUGS IF THE TEXTURE ADDRESS DOESN'T CONTAIN WHITE SPACES!!

		std::getline(ifStream, textureAddress);

		//clean up
		cleanUp();

		map.resize(maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t x{ 0 }; x < maxSize.x; x++) {
			for (size_t y{ 0 }; y < maxSize.y; y++) {
				map[x].resize(maxSize.y, std::vector<Tile*>());
				for (size_t z{ 0 }; z < layers; z++) {
					map[x][y].resize(layers, nullptr);
				}
			}
		}
		
		if (!tileSheet.loadFromFile(textureAddress))
			std::cout << "Error::TileMap::Couldn't load texture, file name:" << textureAddress << '\n';

		unsigned x{}, y{}, z{}, textureRectX{}, textureRectY{};
		bool collision{ false };
		short type{ 0 };

		while (ifStream >> x >> y >> z >> textureRectX >> textureRectY >> collision >> type) {
			map[x][y][z] = new Tile(x, y, gridSizef, tileSheet,
				sf::IntRect(textureRectX, textureRectY, gridSizeU, gridSizeU), collision, type);
		}
	}
	else {
		std::cout << "Error::TileMap::Couldn't open file, file name:" << fileName << '\n';
	}

	ifStream.close();
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

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect,
	const bool collision, const short type)
{
	if (x >= 0 && y >= 0 && z >= 0 &&  x < maxSize.x && y < maxSize.y && z < layers) { 
		if (map[x][y][z] == nullptr) {
			map[x][y][z] = new Tile(x, y, gridSizef, tileSheet, textureRect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x >= 0 && y >= 0 && z >= 0 && x < maxSize.x && y < maxSize.y && z < layers) {
		if (map[x][y][z] != nullptr) {
			delete map[x][y][z];
			map[x][y][z] = nullptr;
		}
	}
}




