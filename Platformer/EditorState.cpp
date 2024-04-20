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

void EditorState::initializetexts()
{
	cursorText.setFont(font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(16);
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
	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	selectorRect.setTexture(tileMap->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, gridSize, tileMap->getTileSheet());
}

void EditorState::initializeTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 60, 34);

}

EditorState::EditorState(StateData* stateData) :
	State(stateData), pauseMenu(*window, font), textureRect(0, 0, gridSize, gridSize)
{
	initializeFonts();
	initializetexts();
	initializeKeyBinds();
	initializeButtons();
	initializeTileMap();
	initializeGUI();
}

EditorState::~EditorState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		delete it->second;

	delete tileMap;
	tileMap = nullptr;

	delete textureSelector;
	textureSelector = nullptr;
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
		if (!textureSelector->getActive())
			tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);
		else
		{
			textureRect = textureSelector->getTextureRect();
		}
	} 
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyCooldown()) {
		if (!textureSelector->getActive())
			tileMap->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
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
	textureSelector->update(mousePosWindow);
	if (!textureSelector->getActive()) {
		selectorRect.setPosition(mousePosGrid.x	 * gridSize, mousePosGrid.y * gridSize);
		selectorRect.setTextureRect(textureRect); 
	}

	cursorText.setPosition(mousePosView.x + 20.f, mousePosView.y - 20.f);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << 
		"\n" << mousePosGrid.x << " " << mousePosGrid.y <<
		"\n" << textureRect.left << " " << textureRect.top;
	cursorText.setString(ss.str());

}

void EditorState::renderGUI(sf::RenderTarget* target)
{
	if(!textureSelector->getActive())
		target->draw(selectorRect);

	//REMOVE LATER
	textureSelector->render(*target);
	target->draw(cursorText);
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
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->render(target);
}


