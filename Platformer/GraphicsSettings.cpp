#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
	contextSettings.antialiasingLevel = 8;
}

void GraphicsSettings::saveToFile(const std::string path) {
	std::ofstream ofstream(path);

	if (ofstream.is_open()) {
		ofstream << title;
		ofstream << resolution.width << resolution.height;
		ofstream << fullScreen;
		ofstream << frameRateLimit;
		ofstream << verticalSync;
		ofstream << contextSettings.antialiasingLevel;
	}
	ofstream.close();
}

void GraphicsSettings::loadFromFile(const std::string path) {

	std::ifstream ifstream(path);

	if (ifstream.is_open()) {
		std::getline(ifstream, title);
		ifstream >> resolution.width >> resolution.height;
		ifstream >> fullScreen;
		ifstream >> frameRateLimit;
		ifstream >> verticalSync;
		ifstream >> contextSettings.antialiasingLevel;
	}
	ifstream.close();
}