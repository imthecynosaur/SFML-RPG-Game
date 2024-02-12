#include "Player.h"

void Player::initializeComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture)
{
	setTexture(texture);
	setPosition(x, y);

	createMovementComponent(1000.f, 8.f, 4.f);
	createAnimationComonent(sprite, texture);

	animationComponent->addAnimation("Idle", 100.f, 0, 0, 4, 0, 128, 128);
}

Player::~Player()
{
}
