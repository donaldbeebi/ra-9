
#pragma once
#include "Puzzle.h"

class NumberPuzzle : public Puzzle {
private:
	std::string m_NumberInput;
	std::string m_Answer;
	bool m_CheckAnswer;
	
public:
	void input(char input);
	NumberPuzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	virtual void enable() override;
	virtual void update() override;
};