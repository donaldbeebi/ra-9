#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Debugger {
private:
	Text m_Text;
	Font m_Font;

public:
	Debugger() { 
		m_Font.loadFromFile("fonts/default.ttf"); 
		m_Text.setFont(m_Font); 
		m_Text.setString("");
		m_Text.setPosition(0.0f, 0.0f);
		m_Text.setFillColor(Color::Red);
	}
	void print(std::string text) { m_Text.setString(text); }
	void draw(RenderWindow& window) { window.draw(m_Text); }
};