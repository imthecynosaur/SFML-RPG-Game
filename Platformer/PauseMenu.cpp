#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) :
	font(font)
{
	background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y) / 2.f));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 2.f - (container.getSize().x / 2.f),
														   static_cast<float>(window.getSize().y) / 2.f - (container.getSize().y / 2.f)));

	menuText.setFont(font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize(24);
	menuText.setString("Paused");
	menuText.setPosition(container.getPosition().x + (container.getSize().x / 2.f) - 10.f, container.getPosition().y + 10.f);

	initializeButtons();
}

PauseMenu::~PauseMenu()
{
	for (auto& it : buttons) {
		delete it.second;
		it.second = nullptr;
	}
}

//std::map<std::string, Button*>& PauseMenu::getButtons()
//{
//	return buttons;
//}

//void PauseMenu::addButton(const std::string key, const std::string text, float x, float y)
//{
//	buttons.emplace(key, new Button(x, y, 40, 35,
//		&font, text,
//		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
//}

void PauseMenu::initializeButtons()
{
	buttons.emplace("Quit", new gui::Button(container.getPosition().x + (container.getSize().x / 2.f) - 10.f,
		container.getPosition().y + container.getSize().y - 50.f,
		40, 35,
		&font, "Quit",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

bool PauseMenu::isButtonPressed(const std::string key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& it : buttons)
		it.second->update(mousePos);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& button : buttons)
		button.second->render(&target);

	target.draw(menuText);
}
