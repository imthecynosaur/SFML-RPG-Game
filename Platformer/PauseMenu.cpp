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
}

PauseMenu::~PauseMenu()
{
	for (auto& it : buttons) {
		delete it.second;
		it.second = nullptr;
	}
}

void PauseMenu::update()
{
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& button : buttons)
		button.second->rener(&target);

	target.draw(menuText);
}
