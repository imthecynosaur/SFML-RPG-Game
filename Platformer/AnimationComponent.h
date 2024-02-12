#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
class AnimationComponent
{
public:
	class Animation
	{
		sf::Sprite& sprite;
		const sf::Texture& textureSheet;
		int width{ 0 };
		int height{ 0 };
		int currnetFrameIndex{ 0 };
		int numberOfFrames{ 0 };
		float elapsedTime{ 0 };
		sf::IntRect* rect{ nullptr };
		bool isTextureSet{ false };
	public:
		std::string name{ "" };

		Animation(sf::Sprite& sprite, const sf::Texture& textureSheet, std::string name, int width, int height, int numberOfFrames);
		~Animation();

		void play(const float& deltaTime);
		void reset();
	};

private:
	sf::Sprite& sprite;
	std::map<std::string, sf::Texture>* textures;
	std::map<std::string, Animation*> animations;
	Animation* currentAnimation{ nullptr };
	Animation* newAnimation{ nullptr };

	
public:
	AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>* textures);
	~AnimationComponent();

	void update(const float& deltaTime, std::string animationName);
};

