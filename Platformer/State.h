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
	float keyLastPressed{ 0.f };		// time elapsed since key was last pressed
	float keyCooldown{ 10.f };

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

	void updateKeyLastPressed(const float& deltaTime);
	const bool getKeyCooldown();

	void updateMousePositions();
	
	void pauseState();
	void unpauseState();

	virtual void endState();
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};