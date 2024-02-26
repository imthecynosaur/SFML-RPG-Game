#pragma once
#include "Button.h"
class PauseMenu
{
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

	
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();
	//std::map<std::string, Button*>& getButtons();
	
	//void addButton(const std::string key, const std::string text, float x, float y);
	void initializeButtons();
	bool isButtonPressed(const std::string key);

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

