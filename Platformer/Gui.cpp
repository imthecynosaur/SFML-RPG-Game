#include "stdafx.h"
#include "Gui.h"
#include <functional>

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id, bool isCircle, float radius) :
	font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor), id(id)
{
	buttonState = BTN_IDLE;
	if (!isCircle)
		shape = new sf::RectangleShape(sf::Vector2f(width, height));
	else
		shape = new sf::CircleShape(radius, 300);

	shape->setPosition(sf::Vector2f(x, y));
	shape->setFillColor(idleColor);
	

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setCharacterSize(26);
	this->text.setPosition(sf::Vector2f(x + (width / 2.f) - (this->text.getGlobalBounds().width / 2),
		y + (height / 2.f) - (this->text.getGlobalBounds().height / 2)));
}

gui::Button::~Button()
{
	delete shape;
	shape = nullptr;
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

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	buttonState = BTN_IDLE;
	if (shape->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
		buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			buttonState = BTN_PRESSED;
	}
	switch (buttonState) {
	case BTN_IDLE:
		shape->setFillColor(idleColor);
		text.setFillColor(sf::Color(150, 150, 150, 200));
		break;
	case BTN_HOVER:
		shape->setFillColor(hoverColor);
		text.setFillColor(sf::Color(250, 250, 250, 250));
		break;
	case BTN_PRESSED:
		shape->setFillColor(activeColor);
		text.setFillColor(sf::Color(20, 20, 20, 50));
		break;
	default:
		shape->setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(*shape);
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

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& deltaTime)
{
	activeElement->update(mousePosWindow);

	if (updateCooldownTimer(deltaTime) && activeElement->isPressed()) {
		cooldownTimer = 0.f;
		visible = !visible;
	}

	if (visible) {
		for (auto& button : list) {
			button->update(mousePosWindow);
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





// --------------------------------TextureSelector----------------------------------------//




gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize,
	const sf::Texture* textureSheet, sf::Font& font) :
	gridSize(gridSize)
{
	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x, y);
	bounds.setFillColor(sf::Color(50, 50, 50, 100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setTexture(*textureSheet);
	sheet.setPosition(x, y);

	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width) {
		sheet.setTextureRect(sf::IntRect(0, 0, bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));
	}
	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width) {
		sheet.setTextureRect(sf::IntRect(0, 0, sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));
	}

	selector.setPosition(x, y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = gridSize;
	textureRect.height = gridSize;

	hideBtn = new Button(x, y + 500, 20, 20, &font, "",
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50));
}

gui::TextureSelector::~TextureSelector()
{
	delete hideBtn;
	hideBtn = nullptr;
}

bool gui::TextureSelector::getHidden()
{
	return hidden;
}

void gui::TextureSelector::setHidden(bool value)
{
	hidden = value;
}

bool gui::TextureSelector::updateCooldownTimer(const float& deltaTime)
{
	if (cooldownTimer < keyCooldown) {
		cooldownTimer += 50.f * deltaTime;
		return false;
	}
	return true;
}

const bool& gui::TextureSelector::getActive() const
{
	return active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return textureRect;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePoswindow, const float& deltaTime)
{
	hideBtn->update(mousePoswindow);

	if (updateCooldownTimer(deltaTime) && hideBtn->isPressed()) {
		/*hidden = !hidden;
		cooldownTimer = 0;*/
	}

	if (!hidden) {
		if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePoswindow)))
			active = true;
		else
			active = false;

		if (active) {
			mousePosGrid.x = (mousePoswindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<int>(gridSize);
			mousePosGrid.y = (mousePoswindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<int>(gridSize);

			selector.setPosition(bounds.getPosition().x + mousePosGrid.x * gridSize,
				bounds.getPosition().y + mousePosGrid.y * gridSize);

			textureRect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
			textureRect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if (!hidden) {
		target.draw(bounds);
		target.draw(sheet);
		if (active)
			target.draw(selector);
	}

	//hideBtn->render(&target);
}
