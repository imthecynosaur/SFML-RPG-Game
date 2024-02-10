#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
class MovementComponent
{
	sf::Sprite& sprite;
	float maxVelocity{ 0 };
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

public:
	MovementComponent(sf::Sprite&, float maxVelocity);
	~MovementComponent();

	const sf::Vector2f getVelocity() const;

	void move(const float dir_x, const float dir_y, const float deltaTime);
	void update(const float& deltaTime);
};

