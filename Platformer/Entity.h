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
	sf::Texture* texture{nullptr};
	sf::Sprite* sprite{nullptr};
	float movementSpeed{ 100.f };

public:
	Entity();
	virtual ~Entity();

	void createSprite(sf::Texture* texture);
	virtual void move(const float deltaTime, const float dir_x, const float dir_y);
	virtual void setPosition(const float x, const float y);

	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);

};

