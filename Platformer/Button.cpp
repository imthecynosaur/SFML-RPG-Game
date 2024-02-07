#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
	font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	buttonState = IDLE;
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(16);
	this->text.setPosition(sf::Vector2f(x + (width / 2.f) - (this->text.getGlobalBounds().width / 2),
		y + (height / 2.f) - (this->text.getGlobalBounds().height / 2)));


	shape.setFillColor(idleColor);
}

Button::~Button()
{
}

const bool Button::isPressed()
{
	if (buttonState == PRESSED)
		return true;
	return false;
}

void Button::update(const sf::Vector2f mousePosition)
{
	buttonState = IDLE;
	if (shape.getGlobalBounds().contains(mousePosition)) {
		buttonState = HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			buttonState = PRESSED;
	}
	switch (buttonState) {
	case IDLE:
		shape.setFillColor(idleColor);
		break;
	case HOVER:
		shape.setFillColor(hoverColor);
		break;
	case PRESSED:
		shape.setFillColor(activeColor);
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
