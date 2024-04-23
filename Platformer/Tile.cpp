#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(unsigned gridX, unsigned gridY, float gridSizeF, const sf::Texture& texture,
	const sf::IntRect & textureRect, bool collision, short type) :
	collision{collision}, type{type}
{
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::White);
	//shape.setOutlineColor(sf::Color::Black);
	//shape.setOutlineThickness(1.f);
	shape.setPosition(static_cast<float>(gridX) * gridSizeF, static_cast<float>(gridY) * gridSizeF);
	shape.setTexture(&texture);
	shape.setTextureRect(textureRect);
}

Tile::~Tile()
{
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << shape.getTextureRect().left << " " << shape.getTextureRect().top << " " << collision << " " << type;
	return ss.str();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
