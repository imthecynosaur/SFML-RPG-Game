#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(x, y);
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
