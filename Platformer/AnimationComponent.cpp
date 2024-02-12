#include "AnimationComponent.h"

AnimationComponent::Animation::Animation(sf::Sprite& sprite, const sf::Texture& textureSheet, std::string name, int width, int height, int numberOfFrames):
	sprite(sprite), textureSheet(textureSheet), name(name), width(width), height(height), numberOfFrames(numberOfFrames)
{
	rect = new sf::IntRect(0, 0, width, height);
}

AnimationComponent::Animation::~Animation()
{
	delete rect;
	rect = nullptr;
}

void AnimationComponent::Animation::play(const float& deltaTime)
{
	if (!isTextureSet) {
		sprite.setTexture(textureSheet);
		sprite.setTextureRect(*rect);
		isTextureSet = true;
	}
	elapsedTime += deltaTime;
	if (elapsedTime >= 0.1f) {
		if (currnetFrameIndex == numberOfFrames - 1) {
			currnetFrameIndex = 0;
		}
		else {
			++currnetFrameIndex;
		}
		rect->left = currnetFrameIndex * width;
		sprite.setTextureRect(*rect);
		elapsedTime = 0;
	}
}

void AnimationComponent::Animation::reset()
{
	isTextureSet = false;
	currnetFrameIndex = 0;
	elapsedTime = 0;
}


AnimationComponent::AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>* textures) :
	sprite(sprite), textures(textures)
{
	for (const auto& it : *textures) {
		animations[it.first] = new Animation(sprite, it.second, it.first, it.second.getSize().y, it.second.getSize().y, it.second.getSize().x / it.second.getSize().y);
	}
}

AnimationComponent::~AnimationComponent()
{
	for (auto& it : animations) {
		delete it.second;
		it.second = nullptr;
	}
}


void AnimationComponent::update(const float& deltaTime, std::string animationName)
{
	newAnimation = animations[animationName];
	if (currentAnimation != newAnimation) {
		if (currentAnimation)
			currentAnimation->reset();
		currentAnimation = newAnimation;
	}
	currentAnimation->play(deltaTime);
}
