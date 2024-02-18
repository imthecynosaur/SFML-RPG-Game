#pragma once
#include "SFML/Graphics.hpp"

enum ButtonStates{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button
{
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();
	
	const bool isPressed();
	void update(const sf::Vector2f mousePosition);
	void rener(sf::RenderTarget* target);
};

