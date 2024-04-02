#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	delete hitBoxComponent;
	hitBoxComponent = nullptr;

	delete movementComponent;
	movementComponent = nullptr;

	delete animationComponent;
	animationComponent = nullptr;
}

void Entity::createHitBoxComponent(float offset_x, float offset_y, float width, float height)
{
	hitBoxComponent = new HitBoxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComonent(sf::Texture& texture)
{
	animationComponent = new AnimationComponent(sprite, texture);
}

void Entity::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void Entity::move(const float dir_x, const float dir_y, const float deltaTime)
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

void Entity::render(sf::RenderTarget& target)
{
		target.draw(sprite);
		if (hitBoxComponent)
			hitBoxComponent->render(target);
}
