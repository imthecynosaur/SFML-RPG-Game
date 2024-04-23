#pragma once

enum TileTypes {DEFAULT, DAMAGING};

class Tile
{
protected:
	sf::RectangleShape shape;
	bool collision{ false };
	short type{ 0 };

public:
	Tile();
	Tile(unsigned gridX, unsigned gridY, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect,
		bool collision = false, short type = TileTypes::DEFAULT);
	~Tile();

	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

