#include "Player.h"

void Player::initializeComponents()
{
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
