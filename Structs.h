#pragma once
#include <string>

struct DialogueState {
	std::string speaker;
	int currentSection;
	bool complete;

	DialogueState(std::string speaker, int currentSection, bool complete) {
		this->speaker = speaker;
		this->currentSection = currentSection;
		this->complete = complete;;
	}
};

struct DialogueLine {
	std::string speaker;
	std::string line;

	DialogueLine(std::string speaker, std::string line) {
		this->speaker = speaker;
		this->line = line;
	}
};
