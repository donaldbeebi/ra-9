#include "TextureManager.h"

using namespace sf;

std::map<std::string, sf::Texture> TextureManager::m_TextureMap;

//POTENTIAL ERROR: NOT USING "getTexture(std::string const& filename)" (not using a reference)
Texture& TextureManager::getTexture(std::string const filename) {
	std::map<std::string, Texture>::iterator targetTexture = m_TextureMap.find(filename);
	if (targetTexture == m_TextureMap.end()) {
		//Texture not found
		Texture& temp = m_TextureMap[filename];
		temp.loadFromFile(filename);
		return temp;
	}
	else {
		//Texture found
		return (*targetTexture).second;
	}
}