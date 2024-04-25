#include "stdafx.h"
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorState.h"


void EditorState::initializeView()
{
	view.setSize(sf::Vector2f(stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height));
	view.setCenter(stateData->gfxSettings->resolution.width / 2.f, stateData->gfxSettings->resolution.height / 2.f);
}

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
	buttons["Hide_Selector"] = new gui::Button(20, 500, 20, 20, &font, "",
		sf::Color(245, 39, 106, 195), sf::Color(245, 39, 106, 255), sf::Color(120, 120, 120, 150),
		0, true, 10);

	buttons["save"] = new gui::Button(20, 540, 20, 20, &font, "",
		sf::Color(67, 255, 163, 190), sf::Color(67, 255, 163, 255), sf::Color(120, 120, 120, 150),
		0, true, 10);

	buttons["load"] = new gui::Button(20, 580, 20, 20, &font, "",
		sf::Color(67, 124, 255, 190), sf::Color(67, 124, 255, 255), sf::Color(120, 120, 120, 150),
		0, true, 10);

	buttons["Hide_SideBar"] = new gui::Button(20, 40, 20, 20, &font, "",
		sf::Color(245, 234, 39, 85), sf::Color(245, 234, 39, 160), sf::Color(120, 120, 120, 150),
		0, true, 10);

}

void EditorState::initializeGUI()
{
	sidebar.setSize(sf::Vector2f(64.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
	sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	sidebar.setOutlineThickness(1.f);

	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	selectorRect.setTexture(tileMap->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(80.f, 20.f, 500.f, 500.f, gridSize, tileMap->getTileSheet(), font);
}

void EditorState::initializeTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 60, 34, "Assets/Texture/TX_Tileset_Grass.png");

}

EditorState::EditorState(StateData* stateData) :
	State(stateData), pauseMenu(*window, font), textureRect(0, 0, gridSize, gridSize)
{
	initializeView();
	initializeFonts();
	initializetexts();
	initializeKeyBinds();
	initializeButtons();
	initializeTileMap();
	initializeGUI();
}

EditorState::~EditorState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
		it->second = nullptr;
	}

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

void EditorState::updateEditorInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP")))) {
		view.move(0.f, -cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN")))) {
		view.move(0.f, cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT")))) {
		view.move(-cameraSpeed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT")))) {
		view.move(cameraSpeed * deltaTime, 0.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyCooldown()) {
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
			if (!textureSelector->getActive())
				tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, type);
			else
			{
				textureRect = textureSelector->getTextureRect();
			}
		}
	} 
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyCooldown()) {
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
			if (!textureSelector->getActive())
				tileMap->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION"))) && getKeyCooldown()) {
		collision = !collision;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("INC_TYPE"))) && getKeyCooldown()) {
		++type;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DEC_TYPE"))) && getKeyCooldown()) {
		if (type > 0)
			--type;
	}

}

void EditorState::update(const float& deltaTime)
{
	updateMousePositions(&view);
	updateKeyLastPressed(deltaTime);
	updateInput(deltaTime);

	if (!paused) {
		updateGUI(deltaTime);
		updateButtons();
		updateEditorInput(deltaTime);
	}
	else {
		pauseMenu.update(mousePosWindow);
		if (pauseMenu.isButtonPressed("Quit"))
			endState();
	}
}

void EditorState::updateButtons()
{
	for (const auto& it : buttons)
		it.second->update(mousePosWindow);

	if (buttons["Hide_Selector"]->isPressed() && getKeyCooldown())
		textureSelector->setHidden(!textureSelector->getHidden());
	
	if (buttons["save"]->isPressed() && getKeyCooldown())
		tileMap->saveToFile("Config/testmap.slmp");

	if (buttons["load"]->isPressed() && getKeyCooldown())
		tileMap->loadFromFile("Config/testmap.slmp");

}

void EditorState::updateGUI(const float& deltaTime)
{
	textureSelector->update(mousePosWindow, deltaTime);
	if (!textureSelector->getActive()) {
		selectorRect.setPosition(mousePosGrid.x	 * gridSize, mousePosGrid.y * gridSize);
		selectorRect.setTextureRect(textureRect); 
	}

	cursorText.setPosition(mousePosView.x + 20.f, mousePosView.y - 20.f);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y <<
		"\n" << mousePosGrid.x << " " << mousePosGrid.y <<
		"\n" << textureRect.left << " " << textureRect.top <<
		"\nCollision : " << collision <<
		"\nType" << type;
	cursorText.setString(ss.str());

}

void EditorState::renderGUI(sf::RenderTarget* target)
{
	if (!textureSelector->getActive() && !sidebar.getGlobalBounds().contains(mousePosView)) {
		target->setView(view);
		target->draw(selectorRect);
	}
	target->setView(window->getDefaultView());
	textureSelector->render(*target);
	target->draw(sidebar);

	target->setView(view);
	target->draw(cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->setView(view);
	tileMap->render(*target);

	target->setView(window->getDefaultView());
	renderGUI(target);
	renderButtons(target);

	if (paused) {
		target->setView(window->getDefaultView());
		pauseMenu.render(*target);
	}
}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	target->setView(window->getDefaultView());
	for (const auto& it : buttons)
		it.second->render(target);
}


