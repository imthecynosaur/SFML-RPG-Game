#include "SettingsState.h"
#include <sstream>



void SettingsState::initializeKeyBinds()
{
	std::ifstream ifstream("Config/mainMenuState_keybinds.ini");
	if (ifstream.is_open()) {
		std::string command{ "" };
		std::string key{ "" };
		while (ifstream >> command >> key)
			keybinds[command] = supportedKeys->at(key);
	}
	ifstream.close();
}

void SettingsState::initializeButtons()
{
	buttons.emplace("EXIT_STATE", new Button(1100, 1000, 40, 35,
		&font, "Quit",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeKeyBinds();
	initializeButtons();

	if (!backGround.loadFromFile("Assets/background/background.jpg"))
		throw "EditorState FAILED TO LOAD BACKGROUND";

	BGSprite.setTexture(backGround);
}

SettingsState::~SettingsState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
		it->second = nullptr;
	}
}

void SettingsState::updateInput(const float& deltaTime)
{
}

void SettingsState::update(const float& deltaTime)
{
	updateMousePositions();
	updateInput(deltaTime);

	updateButtons();
}

void SettingsState::updateButtons()
{
	for (const auto& it : buttons)
		it.second->update(mousePosView);

	if (buttons["EXIT_STATE"]->isPressed())
		endState();
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(BGSprite);
	renderButtons(target);

	//REMOVE LATER
	sf::Text mousePositionText;
	mousePositionText.setPosition(mousePosView.x, mousePosView.y - 15);
	mousePositionText.setFont(font);
	mousePositionText.setCharacterSize(12);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mousePositionText.setString(ss.str());
	target->draw(mousePositionText);
}

void SettingsState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->rener(target);
}

