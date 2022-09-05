#include "DialogueComponent.h"

DialogueComponent::DialogueComponent(std::string speaker, float tileRange, bool printWithTitle) {
	m_Speaker = speaker;
	m_NumberOfLines = 0;
	m_CurrentLine = 0;
	m_CurrentSection = 0;
	m_PrintWithTitle = printWithTitle;
	m_Type = "none";
	m_Range = tileRange * 64.0f;
	m_TempInput = 0;
	m_AutoSection = true;

	//Processing file
	std::ifstream inputFile;

	inputFile.open("dialogues/" + speaker + ".txt");
	std::string line;
	m_NumberOfLines = 0;
	m_NumberOfSections = -1;

	while (std::getline(inputFile, line)) {
		if (line[0] == '{') {
			m_SectionLocations.push_back(m_NumberOfLines);
			m_NumberOfSections++;
		}
		m_Lines.push_back(line);
		insertNewLine(m_Lines[m_NumberOfLines]);
		m_NumberOfLines++;
	}

	m_Triggered = false;
}

void DialogueComponent::setCustomTitle(std::string name) {
	m_Speaker = name;
}

void DialogueComponent::insertNewLine(std::string& line) {
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == '|') line[i] = '\n';
	}
}

void DialogueComponent::trigger(std::string type) {
	m_Triggered = true;
	m_Type = type;
}

void DialogueComponent::triggerInput(int input) {
	m_Triggered = true;
	m_Type = "input";
	m_TempInput = input;
}

DialogueLine DialogueComponent::getDialogueLine() {
	if (m_Triggered) {
		if (m_Type == "inspect") {
			if (m_CurrentLine != m_SectionLocations[m_CurrentSection + 1] - 1) {
				m_CurrentLine++;
			}
			else {
				m_CurrentLine = m_SectionLocations[m_CurrentSection];
				m_Triggered = false;
				m_Type = "none";
				if (m_AutoSection) nextSection();
				return DialogueLine(m_Speaker, "[END]");
			}
			return DialogueLine(m_Speaker, m_Lines[m_CurrentLine]);
		}
		else if (m_Type == "input") {
			if (m_CurrentLine != m_SectionLocations[m_CurrentSection + 1] - 1) {
				m_CurrentLine++;
			}
			else {
				m_CurrentLine = m_SectionLocations[m_CurrentSection];
				m_Triggered = false;
				m_Type = "none";
				if(m_AutoSection) nextSection();
				return DialogueLine(m_Speaker, "[END]");
			}
			std::string temp = m_Lines[m_CurrentLine];
			int pos = temp.find("%");
			if (pos != std::string::npos) {
				temp.erase(pos, 1);
				temp.insert(pos, std::to_string(m_TempInput));
			}
			//m_Type = "inspect";
			return DialogueLine(m_Speaker, temp);
		}
	}
	return DialogueLine(m_Speaker, "none");
}

bool DialogueComponent::printWithTitle() {
	return m_PrintWithTitle;
}

void DialogueComponent::previousSection() {
	if (m_CurrentSection != 0) {
		m_CurrentSection--;
		m_CurrentLine = m_SectionLocations[m_CurrentSection];
	}
}

void DialogueComponent::nextSection() {
	if (m_CurrentSection < m_NumberOfSections - 1) {
		m_CurrentSection++;
		m_CurrentLine = m_SectionLocations[m_CurrentSection];
	}
}

void DialogueComponent::setSection(int section) {
	if (!(section < 0) && !(section > m_NumberOfSections)) {
		m_CurrentSection = section;
		m_CurrentLine = m_SectionLocations[m_CurrentSection];
	}
}

void DialogueComponent::disableAutoSection() {
	m_AutoSection = false;
}

float DialogueComponent::getRange() {
	return m_Range;
}

void DialogueComponent::resetCurrentSection() {
	m_CurrentLine = m_SectionLocations[m_CurrentSection];
	m_Triggered = false;
	m_Type = "none";
}