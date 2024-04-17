#pragma once
class Tile
{
protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect);
	~Tile();

	void update();
	void render(sf::RenderTarget& target);
};

