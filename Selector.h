#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include "TextureManager.h"
#include "Button.h"

class Selector {
private:
	int m_NumOfButtons = 0;
	sf::Sprite m_CursorSprite;
	std::shared_ptr<std::vector<std::shared_ptr<Button>>> m_Buttons;
	int m_CurrentButton;
	bool m_ButtonPressed;
	bool m_Hidden;

public:
	//Internal function
	void setCursor();
	void resetCursor();

	Selector(std::shared_ptr<std::vector<std::shared_ptr<Button>>> buttons);
	void previousButton();
	void nextButton();
	void pushButton();
	void releaseButton();
	std::string getAction();
	void draw(RenderWindow& window);
};