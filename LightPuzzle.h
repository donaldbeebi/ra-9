#pragma once
#include "Puzzle.h"

class LightPuzzle : public Puzzle {
public:
	LightPuzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	virtual void enable() override;
	virtual void update() override;
};