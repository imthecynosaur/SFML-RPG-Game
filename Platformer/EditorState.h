#pragma once
class PauseMenu;

class EditorState :
    public State
{
	sf::Font font;
	sf::Text cursorText;
	PauseMenu pauseMenu;

	std::map<std::string, gui::Button*> buttons;
	
	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	void initializeFonts();
	void initializetexts();
	void initializeKeyBinds();
	void initializeButtons();
	void initializeTileMap();
	void initializeGUI();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	void updateInput(const float& deltaTime);
	void updateEditorInput(const float& dt);
	void update(const float& deltaTime);
	void updateButtons();
	void updateGUI(const float& deltaTime);
	void renderGUI(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target);
};

