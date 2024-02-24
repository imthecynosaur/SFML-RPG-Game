#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height) :
	sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	hitBox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitBox.setSize(sf::Vector2f(width, height));
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineThickness(1.f);
	hitBox.setOutlineColor(sf::Color::Green);
}

HitBoxComponent::~HitBoxComponent()
{
}

bool HitBoxComponent::checkIntersect(const sf::FloatRect& rect)
{
	return hitBox.getGlobalBounds().intersects(rect);
}

void HitBoxComponent::update()
{
	hitBox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitBoxComponent::render(sf::RenderTarget* target)
{
	target->draw(hitBox);
}
