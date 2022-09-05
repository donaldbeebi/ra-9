#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Portrait {
private:
	Sprite m_Sprite;
	int m_MaxStates;
	int m_State;
	IntRect m_TextRect;
	bool m_Showing;

public:
	Portrait(Vector2f initialPositon);
	void setPortrait(int state);

	void show();
	void hide();
	bool isShowing();

	void draw(RenderWindow& window);
};