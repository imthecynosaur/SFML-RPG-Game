#pragma once

enum movement_states { IDLE, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};
class MovementComponent
{
	sf::Sprite& sprite;
	float maxVelocity{ 0 };
	float acceleration{ 0 };
	float deceleration{ 0 };
	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite&, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	const sf::Vector2f getVelocity() const;
	const float getMaxVelocity() const;
	const bool getState(const short unsigned state) const;

	void move(const float dir_x, const float dir_y, const float deltaTime);
	void update(const float& deltaTime);
};

