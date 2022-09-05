#include "NumberPuzzle.h"

NumberPuzzle::NumberPuzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects)
	: Puzzle(name, gameObjects) {
	m_NumberInput = "";
	m_Answer = "8887";
	m_CheckAnswer = false;
}

void NumberPuzzle::input(char input) {
	if (input == 'O') {
		m_CheckAnswer = true;
	}
	else {
		if (m_NumberInput.size() == 4) {
			m_NumberInput[0] = m_NumberInput[1];
			m_NumberInput[1] = m_NumberInput[2];
			m_NumberInput[2] = m_NumberInput[3];
			m_NumberInput[3] = input;
		}
		else m_NumberInput += input;
	}
}

void NumberPuzzle::enable() {
	m_IsEnabled = true;
}

void NumberPuzzle::update() {
	if (m_IsEnabled && !m_IsComplete) {
		if (m_CheckAnswer) {
			if (m_NumberInput == m_Answer) {
				m_IsComplete = true;
			}
			m_CheckAnswer = false;
		}
	}
}