#include "Player.h"

void Player::initializeComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture)
{
	setPosition(x, y);

	createMovementComponent(1000.f, 28.f, 24.f);
	createAnimationComonent(texture);

	animationComponent->addAnimation("Idle", 10.f, 4, 0, 128, 128);
	animationComponent->addAnimation("Walk", 10.f, 5, 1, 128, 128);
	animationComponent->addAnimation("Run", 10.f, 5, 2, 128, 128);
	animationComponent->addAnimation("Attack1", 10.f, 5, 3, 128, 128);
	animationComponent->addAnimation("Attack2", 10.f, 2, 4, 128, 128);
	animationComponent->addAnimation("Attack3", 10.f, 1, 5, 128, 128);
	animationComponent->addAnimation("Attack4", 10.f, 5, 6, 128, 128);
	animationComponent->addAnimation("Jump", 10.f, 5, 7, 128, 128);
	animationComponent->addAnimation("Hurt", 10.f, 1, 8, 128, 128);
	animationComponent->addAnimation("Death", 10.f, 7, 9, 128, 128);
}

Player::~Player()
{
}

void Player::update(const float& deltaTime)
{
	movementComponent->update(deltaTime);
	if (movementComponent->getState(IDLE))
		animationComponent->play("Idle", deltaTime);
	else if (movementComponent->getState(MOVING)) {
		if (movementComponent->getState(MOVING_LEFT))
			animationComponent->play("Walk", deltaTime);
		else if (movementComponent->getState(MOVING_RIGHT))
			animationComponent->play("Run", deltaTime);
	}
}
