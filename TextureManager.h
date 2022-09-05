#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {
private:
	static std::map<std::string, sf::Texture> m_TextureMap;

public:
	static sf::Texture& getTexture(std::string const filename);

};