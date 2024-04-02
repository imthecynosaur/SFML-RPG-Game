#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id) :
	font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor), id(id)
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

gui::Button::~Button()
{
}

const bool gui::Button::isPressed()
{
	if (buttonState == BTN_PRESSED)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return text.getString();
}

const short unsigned& gui::Button::getID()
{
	return id;
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::update(const sf::Vector2f& mousePosition)
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

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}




// --------------------------------DropDownList----------------------------------------//




gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned elementsCount, unsigned defaultIndex) :
	font(font)
{
	activeElement = new Button(x, y, width, height,
		&font, list[0],
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	for (size_t i = 0; i < elementsCount; i++) {
		this->list.push_back(new Button(x , y + (i + 1) * height, width, height,
			&font, list[i],
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0), i));
	}
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	activeElement = nullptr;
	for (auto& button : list) {
		delete button;
		button = nullptr;
	}
}

const unsigned short gui::DropDownList::getActiveElementId() const
{
	return activeElement->getID();
}

bool gui::DropDownList::updateCooldownTimer(const float& deltaTime)
{
	if (cooldownTimer < keyCooldown) {
		cooldownTimer += 50.f * deltaTime;
		return false;
	}
	return true;
}

void gui::DropDownList::update(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	activeElement->update(mousePosition);

	if (updateCooldownTimer(deltaTime) && activeElement->isPressed()) {
		cooldownTimer = 0.f;
		visible = !visible;
	}

	if (visible) {
		for (auto& button : list) {
			button->update(mousePosition);
			if (button->isPressed() && updateCooldownTimer(deltaTime)) {
				visible = false;
				activeElement->setText(button->getText());
				activeElement->setId(button->getID());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget* target)
{
	activeElement->render(target);
	if (visible) {
		for (auto& button : list)
			button->render(target);
	}
}
