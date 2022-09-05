#include "CharacterDialogueComponent.h"

void CharacterDialogueComponent::actCommand(std::string command) {
	if (command == "command_inspect_lightbulb") {
		m_CurrentSectionI = 0;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
	else if (command == "command_inspect_pony") {
		m_CurrentSectionI = 11;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
	else if (command == "inspect") {
		m_CurrentSectionI = m_InspectSection;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
	else if (command == "command_confirm_exit_game") {
		m_CurrentSectionI = 13;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
	else if (command == "command_exit_game") {
		m_CurrentSectionI = 14;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
}

void CharacterDialogueComponent::setSectionI(int section) {
	if (!(section < 0) && !(section > m_NumberOfSectionsI)) {
		m_InspectSection = section;
		m_CurrentSectionI = section;
		m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
	}
}

CharacterDialogueComponent::CharacterDialogueComponent(std::string speaker, float tileRange, bool printWithTitle) 
	: DialogueComponent(speaker, tileRange, printWithTitle) {
	m_NumberOfLinesI = 0;
	m_CurrentLineI = 0;
	m_CurrentSectionI = 0;
	m_InspectSection = 0;
	m_Pony = false;

	//Processing file
	std::ifstream inputFile;

	inputFile.open("dialogues/" + speaker + "_inspect.txt");
	std::string line;
	m_NumberOfLinesI = 0;
	m_NumberOfSectionsI = -1;

	while (std::getline(inputFile, line)) {
		if (line[0] == '{') {
			m_SectionLocationsI.push_back(m_NumberOfLinesI);
			m_NumberOfSectionsI++;
		}
		m_LinesI.push_back(line);
		insertNewLine(m_LinesI[m_NumberOfLinesI]);
		m_NumberOfLinesI++;
	}
}

void CharacterDialogueComponent::trigger(std::string action) {
	DialogueComponent::trigger(action);
	actCommand(m_Type);
}

DialogueLine CharacterDialogueComponent::getDialogueLine() {
	if (m_Triggered) {
		if (m_Type == "dialogue") {
			if (m_CurrentLine != m_SectionLocations[m_CurrentSection + 1] - 1) {
				m_CurrentLine++;
			}
			else {
				m_CurrentLine = m_SectionLocations[m_CurrentSection];
				m_Triggered = false;
				m_Type = "none";
				nextSection();
				return DialogueLine(m_Speaker, "[END]");
			}
			return DialogueLine(m_Speaker, m_Lines[m_CurrentLine]);
		}
		else if (m_Type.find("command") != std::string::npos || m_Type == "inspect") {
			if (m_Type == "command_inspect_pony" && m_Pony) {
				return DialogueLine(m_Speaker, "none");
			}
			else{
				if (m_CurrentLineI != m_SectionLocationsI[m_CurrentSectionI + 1] - 1) {
					m_CurrentLineI++;
				}
				else {
					m_CurrentLineI = m_SectionLocationsI[m_CurrentSectionI];
					m_Triggered = false;
					if (m_Type == "command_inspect_pony") m_Pony = true;
					m_Type = "none";
					if (m_CurrentSectionI == 2) {
						m_InspectSection = 15;
					}
					return DialogueLine(m_Speaker, "[END]");
				}
				return DialogueLine(m_Speaker, m_LinesI[m_CurrentLineI]);
			}
		}
	}
	return DialogueLine(m_Speaker, "none");
}