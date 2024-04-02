#pragma once
#include"MainMenuState.h"

class Game
{
	GraphicsSettings gfxSettings;
	sf::RenderWindow* window{nullptr};
	sf::Event event;

	sf::Clock clock;
	float deltaTime{0.f};

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	void initializeKeys();
	void initializeGraphicsSettings();
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

