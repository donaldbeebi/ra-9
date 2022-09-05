//ABANDONED
#pragma once
#include <SFML/Graphics.hpp>

class Component {
private:
	bool m_Enabled = false;

public:
	void enable() {
		m_Enabled = true;
	}

	void disable() {
		m_Enabled = false;
	}

	virtual void draw(sf::RenderWindow& window){}
	virtual void update(float dt) {};

};