#pragma once
#include "Player.h"
#include "Gui.h"

class State
{
protected:
	sf::Font font;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit{ false };
	bool paused{ false };
	float keyPressedTime{ 0.f };
	float keyPressedTimeMax{ 10.f };

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	std::map<std::string, sf::Texture> textures;

	void initializeFonts();
	virtual void initializeKeyBinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool getQuit() const;

	void updateKeyPressedTime(const float& deltaTime);
	const bool getKeyTime();

	void updateMousePositions();
	
	void pauseState();
	void unpauseState();

	virtual void endState();
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};