#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	sprite = new sf::Sprite(*texture);
}

void Entity::move(const float deltaTime, const float dir_x, const float dir_y)
{
	if (sprite)
		sprite->move(dir_x * movementSpeed * deltaTime, dir_y * movementSpeed * deltaTime);
}

void Entity::setPosition(const float x, const float y)
{
	if (sprite)
		sprite->setPosition(x, y);
}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (sprite)
		target->draw(*sprite);
}
