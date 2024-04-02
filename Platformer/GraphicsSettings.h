#pragma once
class GraphicsSettings {
public:
	GraphicsSettings();
	std::string title{ "" };
	sf::VideoMode resolution{ sf::VideoMode::getDesktopMode() };
	bool fullScreen{ false };
	bool verticalSync{ false };
	unsigned frameRateLimit{ 120 };
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes{ sf::VideoMode::getFullscreenModes() };

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
