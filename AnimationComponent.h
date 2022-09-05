#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

enum class State {};

using namespace sf;

class AnimationComponent {
protected:
	std::string m_TextureName;
	Vector2u m_ImageCount;
	Vector2f m_TextureSize;
	Vector2u m_CurrentImage;
	float m_CurrentSwitchTime;

	float m_TotalTime;
	float m_ConstantSwitchTime;
	std::unique_ptr<std::vector<float>> m_VariedSwitchTimes;
	bool m_HasVariedSwitchTimes;
	bool m_IsStopped;

public:
	IntRect m_TextRect;

	//Initializers
	AnimationComponent(std::string texture, Vector2u imageCount);
	void setConstantSwitchTime(float constantSwitchTime);
	void setVariedSwitchTimes(std::unique_ptr<std::vector<float>> variedSwitchTimes);
	void resetFrame();

	virtual void play();
	void stop();

	std::string getTextureName();
	Vector2f getTextureSize();
	Vector2u getImageCount();

	virtual void update(float dt) = 0;
};