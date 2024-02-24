#pragma once
#include "HitBoxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{

protected:
	sf::Sprite sprite;
	HitBoxComponent* hitBoxComponent{ nullptr };
	MovementComponent* movementComponent{ nullptr };
	AnimationComponent* animationComponent{ nullptr };

public:
	Entity();
	virtual ~Entity();


	void createHitBoxComponent(float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComonent(sf::Texture& texture);
	void setTexture (sf::Texture& texture);
	virtual void move(const float dir_x, const float dir_y, const float deltaTime);
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);

};

