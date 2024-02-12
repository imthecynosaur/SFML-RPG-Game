#pragma once
#include "Entity.h"

class Player :
    public Entity
{
    std::string currentAnimation{ "Idle" };
    void initializeComponents();
    void initializeTextures();

public:
    Player(float x, float y);
    ~Player();

    void update(const float& deltaTime);
};

