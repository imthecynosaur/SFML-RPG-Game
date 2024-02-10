#pragma once
#include "MovementComponent.h"

class Entity
{

protected:
	sf::Sprite sprite;
	MovementComponent* movementComponent{ nullptr };

public:
	Entity();
	virtual ~Entity();


	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void setTexture (sf::Texture& texture);
	virtual void move(const float dir_x, const float dir_y, const float deltaTime);
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);

};

