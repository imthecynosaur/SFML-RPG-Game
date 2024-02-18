#include "AnimationComponent.h"

AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
	float animationTimer,
	int frames_x, int frames_y,
	int width, int height) :
	sprite(sprite), textureSheet(textureSheet),
	animationTimer(animationTimer),
	width(width), height(height)
{
	startRect = sf::IntRect(0 , frames_y * height, width, height);
	endRect= sf::IntRect(frames_x * width , frames_y * height, width, height);
	currentRect = startRect;
	sprite.setTexture(textureSheet, true);
	sprite.setTextureRect(startRect);
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::reset()
{
	timer = 0.f;
	currentRect = startRect;
}

void AnimationComponent::Animation::play(const float& deltaTime)
{
	timer += 100 * deltaTime;
	if (timer >= animationTimer) {
		timer = 0.f;
		if (currentRect != endRect) 
			currentRect.left += width;
		else 
			currentRect.left = startRect.left;
		sprite.setTextureRect(currentRect);
	}
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet) :
	sprite(sprite), textureSheet(textureSheet)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& it : animations) {
		delete it.second;
		it.second = nullptr;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animationTimer,
	int frames_x, int frames_y,
	int width, int height)
{
	animations[key] = new Animation(sprite, textureSheet,
		animationTimer,
		frames_x, frames_y,
		width, height);
}


void AnimationComponent::play(const std::string key, const float& deltaTime)
{
	if (lastPlayedAnimation != animations[key]) {
		if (lastPlayedAnimation == nullptr)
			lastPlayedAnimation = animations[key];
		else {
			lastPlayedAnimation->reset();
			lastPlayedAnimation = animations[key];
		}
	}
	animations[key]->play(deltaTime);
}
