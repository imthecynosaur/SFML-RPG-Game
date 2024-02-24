#pragma once
#include "Entity.h"
class Player :
    public Entity
{
    void initializeComponents();
    bool isAttacking{ false };

public:
    Player(float x, float y, sf::Texture& texture);
    ~Player();

    void attack(const float& deltaTime);
    void update(const float& deltaTime);
};

