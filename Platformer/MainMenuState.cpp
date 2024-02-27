#include "MainMenuState.h"
#include <sstream>



void MainMenuState::initializeKeyBinds()
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

void MainMenuState::initializeButtons()
{
	buttons.emplace("GAME_STATE", new gui::Button(100, 750, 90, 35,
		&font, "New Game",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	buttons.emplace("SETTING_STATE", new gui::Button(100, 850, 70, 35,
		&font, "Settings",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	buttons.emplace("EDITOR_STATE", new gui::Button(1700, 1000, 50, 35,
		&font, "Editor",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	buttons.emplace("EXIT_STATE", new gui::Button(100, 1000, 40, 35,
		&font, "Quit",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeKeyBinds();
	initializeButtons();
	
	if (!backGround.loadFromFile("Assets/background/background.jpg"))
		throw "ERROR::MAIN_MENU:: FAILED TO LOAD BACKGROUND";

	BGSprite.setTexture(backGround);
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
		it->second = nullptr;
	}
}

void MainMenuState::updateInput(const float& deltaTime)
{
}

void MainMenuState::update(const float& deltaTime)
{
	updateMousePositions();
	updateInput(deltaTime);

	updateButtons();
}

void MainMenuState::updateButtons()
{
	for (const auto& it : buttons)
		it.second->update(mousePosView);

	if (buttons["EXIT_STATE"]->isPressed())
		endState();

	if (buttons["GAME_STATE"]->isPressed()) {
		states->push(new GameState(window, supportedKeys, states));
	}
	if (buttons["EDITOR_STATE"]->isPressed()) {
		states->push(new EditorState(window, supportedKeys, states));
	}
	if (buttons["SETTING_STATE"]->isPressed()) {
		states->push(new SettingsState(window, supportedKeys, states));
	}
}

void MainMenuState::render(sf::RenderTarget* target)
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

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->render(target);
}

