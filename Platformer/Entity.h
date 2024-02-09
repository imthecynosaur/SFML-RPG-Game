#pragma once
#include "MovementComponent.h"

class Entity
{

protected:
	sf::Texture* texture{nullptr};
	sf::Sprite* sprite{nullptr};
	MovementComponent* movementComponent{ nullptr };

public:
	Entity();
	virtual ~Entity();


	void createMovementComponent(const float maxVelocity);
	void createSprite(sf::Texture* texture);
	virtual void move(const float deltaTime, const float dir_x, const float dir_y);
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);

};

