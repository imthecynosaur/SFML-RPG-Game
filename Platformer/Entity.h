#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>

class Entity
{

protected:
	sf::RectangleShape shape;
	float movementSpeed{ 100.f };
public:
	Entity();
	virtual ~Entity();

	virtual void move(const float deltaTime, const float dir_x, const float dir_y);

	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);

};

