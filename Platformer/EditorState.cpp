#include "stdafx.h"
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
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
	/*buttons.emplace("GAME_STATE", new gui::Button(100, 750, 90, 35,
		&font, "New Game",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));*/
}

void EditorState::initializeGUI()
{
	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color::Transparent);
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initializeTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 10, 10);

}

EditorState::EditorState(StateData* stateData) :
	State(stateData), pauseMenu(*window, font)
{
	initializeFonts();
	initializeKeyBinds();
	initializeButtons();
	initializeGUI();
	initializeTileMap();
}

EditorState::~EditorState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		delete it->second;

	delete tileMap;
	tileMap = nullptr;
}

void EditorState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyCooldown()) {
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyCooldown()) {
		tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0);
	}
}

void EditorState::update(const float& deltaTime)
{
	updateMousePositions();
	updateKeyLastPressed(deltaTime);
	updateInput(deltaTime);

	if (!paused) {
		updateGUI();
		updateButtons();
		updateEditorInput(deltaTime);
	}
	else {
		pauseMenu.update(mousePosView);
		if (pauseMenu.isButtonPressed("Quit"))
			endState();
	}
}

void EditorState::updateButtons()
{
	for (const auto& it : buttons)
		it.second->update(mousePosView);

}

void EditorState::updateGUI()
{
	selectorRect.setPosition(mousePosGrid.x	 * gridSize, mousePosGrid.y * gridSize);
}

void EditorState::renderGUI(sf::RenderTarget* target)
{
	target->draw(selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	tileMap->render(*target);

	renderGUI(target);
	renderButtons(target);

	if (paused) {
		pauseMenu.render(*target);
	}

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

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->render(target);
}


