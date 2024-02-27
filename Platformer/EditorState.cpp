#include "EditorState.h"

void EditorState::initializeFonts()
{
	if (!font.loadFromFile("Fonts/AGENCYR.TTF"))
		throw("ERROR::EditorState::COULD NOT LOAD FONT");
}

void EditorState::initializeKeyBinds()
{
	std::ifstream ifstream("Config/editorState_keybinds.ini");
	if (ifstream.is_open()) {
		std::string command{ "" };
		std::string key{ "" };
		while (ifstream >> command >> key)
			keybinds[command] = supportedKeys->at(key);
	}
	ifstream.close();
}

void EditorState::initializeButtons()
{
	buttons.emplace("GAME_STATE", new gui::Button(100, 750, 90, 35,
		&font, "New Game",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeFonts();
	initializeKeyBinds();
	initializeButtons();
}

EditorState::~EditorState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		delete it->second;
}

void EditorState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
		endState();
}

void EditorState::update(const float& deltaTime)
{
	updateMousePositions();
	updateInput(deltaTime);

	updateButtons();
}

void EditorState::updateButtons()
{
	for (const auto& it : buttons)
		it.second->update(mousePosView);

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	renderButtons(target);
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->render(target);
}


