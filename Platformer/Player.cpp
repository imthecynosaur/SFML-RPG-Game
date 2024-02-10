#include "Player.h"

void Player::initializeComponents()
{
	createMovementComponent(1000.f, 8.f, 4.f);
}

Player::Player(float x, float y, sf::Texture& texture)
{
	initializeComponents();
	setTexture(texture);
	setPosition(x, y);
}

Player::~Player()
{
}
