#pragma once
#include "Entity.h"
class Player :
    public Entity
{
    void initializeComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    ~Player();

    void update(const float& deltaTime);
};

