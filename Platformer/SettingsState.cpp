#include "stdafx.h"
#include "SettingsState.h"


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
	buttons.emplace("BACK", new gui::Button(120, 1000, 40, 35,
		&font, "Back",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	buttons.emplace("APPLY", new gui::Button(120, 950, 40, 35,
		&font, "Apply",
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));


	std::vector<std::string> vModes;
	for (auto& mode : videoModes)
		vModes.push_back(std::to_string(mode.width) + 'x' + std::to_string(mode.height));

	dropDowns.emplace("Resolution", new gui::DropDownList(100, 100, 100, 45, font, vModes.data(), vModes.size()));
}

void SettingsState::initializeText()
{
	optionsText.setFont(font);
	optionsText.setPosition(sf::Vector2f(10.f, 100.f));
	optionsText.setCharacterSize(20);
	optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	optionsText.setString("Crap \nBullshit \nDogshit \nAss");
}

SettingsState::SettingsState(StateData* stateData) :
	State(stateData)
{
	videoModes = sf::VideoMode::getFullscreenModes();
	initializeKeyBinds();
	initializeGui();
	initializeText();


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
		it.second->update(mousePosWindow);

	if (buttons["BACK"]->isPressed())
		endState();

	if (buttons["APPLY"]->isPressed()) {
		stateData->gfxSettings->resolution = videoModes[dropDowns["Resolution"]->getActiveElementId()];
		window->create(stateData->gfxSettings->resolution, stateData->gfxSettings->title, sf::Style::Default);
	}

	for (const auto& it : dropDowns)
		it.second->update(mousePosWindow, deltaTime);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(BGSprite);
	renderGui(target);

	target->draw(optionsText);

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

