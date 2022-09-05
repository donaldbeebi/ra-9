#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Fader {
private:
	RectangleShape m_Fader;
	bool m_FadingIn;
	bool m_Active;
	bool m_Black;

	float m_Alpha;
	float m_TargetAlpha;

	float m_Rate;
	int m_Color;

public:
	Fader(Vector2f screenSize);
	void setWhite();
	void setTime(float timeInSeconds);

	void fadeIn();
	void fadeIn(int alpha);
	void fadeOut();

	void darken();
	void dim();
	void brighten();

	bool isActive();
	bool isBlack();

	void update(float dt);
	void draw(RenderWindow& window);
};