#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{

protected:
	sf::Sprite sprite;
	std::map<std::string, sf::Texture> textures;
	MovementComponent* movementComponent{ nullptr };
	AnimationComponent* animationComponent{ nullptr };
	short statusCode{ 0 };

public:
	Entity();
	virtual ~Entity();


	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent();
	void setTexture (sf::Texture& texture);
	virtual void initializeTextures() = 0;
	virtual void move(const float dir_x, const float dir_y, const float deltaTime);
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& deltaTime) = 0 ;
	virtual void render(sf::RenderTarget* target);

};

