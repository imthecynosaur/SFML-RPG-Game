#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	
}

void Entity::createMovementComponent(const float maxVelocity)
{
	movementComponent = new MovementComponent(sprite, maxVelocity);
}

void Entity::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void Entity::move(const float deltaTime, const float dir_x, const float dir_y)
{
	if (movementComponent) {
		movementComponent->move(dir_x, dir_y, deltaTime);
	}
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
		target->draw(sprite);
}
