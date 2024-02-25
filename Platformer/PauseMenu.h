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

	void update();
	void render(sf::RenderTarget& target);
};

