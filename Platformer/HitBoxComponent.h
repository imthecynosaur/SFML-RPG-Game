#pragma once
#include "SFML/Graphics.hpp"
class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitBox;

	float offsetX{ 0.f };
	float offsetY{ 0.f };


public:
	HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitBoxComponent();

	bool checkIntersect(const sf::FloatRect& rect);

	void update();
	void render(sf::RenderTarget& target);
};

