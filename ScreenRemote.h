#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

class ScreenRemote {
private:
	std::string m_TargetScreen = "none";

public:
	void switchScreen(std::string targetScreen);
	void exitGame();
	std::string getAction();
};