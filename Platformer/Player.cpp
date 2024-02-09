#include "Player.h"

void Player::initializeComponents()
{
	createMovementComponent(1000.f);
}

Player::Player(float x, float y, sf::Texture* texture)
{
	initializeComponents();
	createSprite(texture);
	setPosition(x, y);
}

Player::~Player()
{
}
