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

void SettingsState::initializeGui()
{
	buttons.emplace("BACK", new gui::Button(1800, 1000, 40, 35,
		&font, "Back",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	buttons.emplace("APPLY", new gui::Button(1800, 950, 40, 35,
		&font, "Apply",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	std::string options[] = { "1920x1080", "800x600", "640x480"};
	dropDowns.emplace("Resolution", new gui::DropDownList(100, 100, 100, 45, font, options, 3, 2));
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeKeyBinds();
	initializeGui();

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

	for (auto& it : dropDowns) {
		delete it.second;
		it.second = nullptr;
	}
}

void SettingsState::updateInput(const float& deltaTime)
{
}

void SettingsState::update(const float& deltaTime)
{
	updateMousePositions();
	updateInput(deltaTime);

	updateGui(deltaTime);
}

void SettingsState::updateGui(const float& deltaTime)
{
	for (const auto& it : buttons)
		it.second->update(mousePosView);

	if (buttons["BACK"]->isPressed())
		endState();

	for (const auto& it : dropDowns)
		it.second->update(mousePosView, deltaTime);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(BGSprite);
	renderGui(target);


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

void SettingsState::renderGui(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->render(target);

	for (const auto& it : dropDowns)
		it.second->render(target);
}

