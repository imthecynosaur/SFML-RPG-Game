#pragma once
#include"States/GameState.h"

class Game
{
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	
	float deltaTime;

	std::stack<State*> states;

	void initializeWindow();
	void initializeStates();

public:
	Game();
	virtual ~Game();

	void endApplication();

	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	void render();

	void run();
};

