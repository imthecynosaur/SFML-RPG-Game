#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
	font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	buttonState = BTN_IDLE;
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setCharacterSize(26);
	this->text.setPosition(sf::Vector2f(x + (width / 2.f) - (this->text.getGlobalBounds().width / 2),
		y + (height / 2.f) - (this->text.getGlobalBounds().height / 2)));


	shape.setFillColor(idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed()
{
	if (buttonState == BTN_PRESSED)
		return true;
	return false;
}

void Button::update(const sf::Vector2f mousePosition)
{
	buttonState = BTN_IDLE;
	if (shape.getGlobalBounds().contains(mousePosition)) {
		buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			buttonState = BTN_PRESSED;
	}
	switch (buttonState) {
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(sf::Color(150, 150, 150, 200));
		break;
	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(sf::Color(250, 250, 250, 250));
		break;
	case BTN_PRESSED:
		shape.setFillColor(activeColor);
		text.setFillColor(sf::Color(20, 20, 20, 50));
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::rener(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
