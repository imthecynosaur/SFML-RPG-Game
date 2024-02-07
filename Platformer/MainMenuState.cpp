#include "MainMenuState.h"

void MainMenuState::initializeFonts()
{
	if (!font.loadFromFile("Fonts/AGENCYR.TTF"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

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
	buttons.emplace("GAME_STATE", new Button(100, 100, 150, 50,
		&font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));

	buttons.emplace("EXIT_STATE", new Button(100, 300, 150, 50,
		&font, "Quit",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	initializeFonts();
	initializeKeyBinds();
	initializeButtons();

	backGround.loadFromFile("Assets/background/background.jpg");
	BGSprite.setTexture(backGround);
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
		delete it->second;
}

void MainMenuState::endState()
{

}

void MainMenuState::updateInput(const float& deltaTime)
{
	checkForQuit();
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
		quit = true;

	if (buttons["GAME_STATE"]->isPressed())
		states->push(new GameState(window, supportedKeys, states));
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(BGSprite);
	renderButtons(target);
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (const auto& it : buttons)
		it.second->rener(target);
}

