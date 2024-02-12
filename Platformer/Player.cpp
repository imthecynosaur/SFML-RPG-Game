#include "Player.h"

void Player::initializeComponents()
{
	createMovementComponent(1000.f, 50.f, 45.f);
	createAnimationComponent();
}

void Player::initializeTextures()
{
	if (!textures["Idle"].loadFromFile("Assets/countess_vampire/Idle.png"))
		std::cout << "didn't load countess Idle" << std::endl;
	if (!textures["Walk"].loadFromFile("Assets/countess_vampire/walk.png"))
		std::cout << "couldn't load walk texture" << std::endl;
	if (!textures["Run"].loadFromFile("Assets/countess_vampire/run.png"))
		std::cout << "couldn't load walk texture" << std::endl;
	if (!textures["Jump"].loadFromFile("Assets/countess_vampire/jump.png"))
		std::cout << "couldn't load walk texture" << std::endl;
}

Player::Player(float x, float y)
{
	initializeTextures();
	initializeComponents();
	setPosition(x, y);
}

Player::~Player()
{
}

void Player::update(const float& deltaTime)
{
	if (movementComponent->getVelocity().x == 0 && movementComponent->getVelocity().y == 0)
		currentAnimation = "Idle";
	else if (movementComponent->getVelocity().x != 0 && movementComponent->getVelocity().y == 0)
		currentAnimation = "Walk";

	movementComponent->update(deltaTime);
	animationComponent->update(deltaTime, currentAnimation);
}
