#pragma once
class PauseMenu;

class EditorState :
    public State
{
	sf::Font font;
	PauseMenu pauseMenu;

	std::map<std::string, gui::Button*> buttons;
	
	TileMap* tileMap;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	void initializeFonts();
	void initializeKeyBinds();
	void initializeButtons();
	void initializeGUI();
	void initializeTileMap();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	void updateInput(const float& deltaTime);
	void updateEditorInput(const float& dt);
	void update(const float& deltaTime);
	void updateButtons();
	void updateGUI();
	void renderGUI(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

