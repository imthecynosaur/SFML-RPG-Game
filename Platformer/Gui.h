#pragma once
#include "SFML/Graphics.hpp"

enum ButtonStates{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

namespace gui
{
	class Button
	{
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:
		Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id = 0);
		virtual ~Button();

		const bool isPressed();
		const std::string getText() const;
		const short unsigned& getID();

		void setText(const std::string text);
		void setId(const short unsigned id);

		void update(const sf::Vector2f& mousePosition);
		void render(sf::RenderTarget* target);
	};

	class DropDownList
	{
		float cooldownTimer{ 0.f };
		float keyCooldown{ 10.f };
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool visible{ false };

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned elementsCount, unsigned defaultIndex = 0);
		~DropDownList();
		bool updateCooldownTimer(const float& deltaTime);
		void update(const sf::Vector2f& mousePosition, const float& deltaTime);
		void render(sf::RenderTarget* target);
	};
}

