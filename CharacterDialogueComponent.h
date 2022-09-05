#pragma once
#include "DialogueComponent.h"

class CharacterDialogueComponent : public DialogueComponent {
private:
	int m_NumberOfLinesI;
	std::vector<std::string> m_LinesI;
	int m_CurrentLineI;
	int m_NumberOfSectionsI;
	std::vector<int> m_SectionLocationsI;
	int m_CurrentSectionI;
	int m_InspectSection; //used to remember where we were at for inspect trigger
	bool m_Pony;

	void actCommand(std::string command);

public:
	CharacterDialogueComponent(std::string speaker, float tileRange, bool printWithTitle);
	
	void setSectionI(int section);

	virtual void trigger(std::string action) override;
	virtual DialogueLine getDialogueLine() override;
};