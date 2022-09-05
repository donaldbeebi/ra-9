//Button class will have three textures - default, pressed
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "TextureManager.h"
#include "SoundManager.h"

using namespace sf;

class Button {
private:
	Sprite m_Sprite;
	std::string m_PushAction;
	std::string m_ReleaseAction;
	std::string m_CurrentAction;
	Vector2f m_Size;
	Vector2f m_CursorCenterPosition;

	bool m_Hidden;

public:
	//Initialization
	Button(std::string texture, std::string pushAction, std::string releaseAction, Vector2f centerPosition);

	void show();
	void hide();
	bool isHidden();

	void setPosition(Vector2f centerPosition);

	Vector2f getCursorCenterPosition();
	void push();
	void release();
	std::string getAction();
	void draw(RenderWindow& window);
};