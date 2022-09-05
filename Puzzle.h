#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

class Puzzle {
protected:
	std::string m_Name;
	bool m_IsEnabled;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> m_TriggerObjects;
	bool m_IsComplete;

public:
	Puzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	virtual void enable() = 0;
	void disable();
	std::string getName();
	bool isComplete();
	virtual void update() = 0;

	//additional function
	virtual void input(char input) {}
	void manualComplete() { m_IsComplete = true; }
};