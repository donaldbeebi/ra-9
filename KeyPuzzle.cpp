#include "KeyPuzzle.h"

KeyPuzzle::KeyPuzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects)
	: Puzzle(name, gameObjects) {}

void KeyPuzzle::enable() {
	m_IsEnabled = true;
}

void KeyPuzzle::update() {}