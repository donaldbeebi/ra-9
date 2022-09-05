#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "TextureManager.h"
#include "LoopedAnimationComponent.h"
#include "TransformComponent.h"

using namespace sf;

class GraphicsComponent {
protected:
	bool m_Enabled;
	Sprite m_Sprite;
	Vector2f m_TextureSize;
	float m_DrawOffsetY;
	float m_TextRectOffsetY;
	IntRect m_TextRect;
	std::shared_ptr<TransformComponent> m_TC = nullptr;
	int m_State;
	unsigned int m_StateCount;

public:
	GraphicsComponent(unsigned int stateCount);
	virtual void disableDrawOffset() {}

	void enable();
	void disable();
	void toggle();
	void toggleState(int state1, int state2);
	bool isEnabled();
	virtual void setState(int state);

	Vector2f getSize();
	int getState();
	unsigned int getStateCount();

	Vector2f getSpritePosition();

	virtual void update(float dt);
	void draw(RenderWindow& window);
};