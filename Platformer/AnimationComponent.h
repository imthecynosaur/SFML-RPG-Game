#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
class AnimationComponent
{
private:
	class Animation
	{
	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		float animationTimer{ 0 };
		float timer{ 0 };
		int width{ 0 };
		int height{ 0 };

		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer,
			int frames_x, int frames_y, int width, int height);
		~Animation();

		void pause();
		void reset();
		void play(const float& deltaTime);
	};


	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map <std::string, Animation*> animations;
	Animation* lastPlayedAnimation{ nullptr };
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	~AnimationComponent();

	void addAnimation(const std::string key,
		float animationTimer,
		int frames_x, int frames_y,
		int width, int height);

	void play(const std::string key, const float& deltaTime);
};

