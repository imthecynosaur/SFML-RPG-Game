#pragma once
#include"State.h"

class Game
{
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	
	double deltaTime;

	void initializeWindow();

public:
	Game();
	virtual ~Game();

	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

