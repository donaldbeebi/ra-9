#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Structs.h"

class DialogueComponent {
protected:
	std::string m_Speaker;

	int m_NumberOfLines;
	std::vector<std::string> m_Lines;
	int m_CurrentLine;
	int m_NumberOfSections;
	std::vector<int> m_SectionLocations;
	int m_CurrentSection;
	int m_TempInput;
	
	bool m_PrintWithTitle;
	std::string m_Type;
	float m_Range;

	bool m_Triggered;

	void insertNewLine(std::string& line);
	
	bool m_AutoSection;

public:
	DialogueComponent(std::string speaker, float tileRange, bool printWithTitle);
	void setCustomTitle(std::string name);
	
	virtual void trigger(std::string type);
	virtual void triggerInput(int input);
	virtual DialogueLine getDialogueLine();
	bool printWithTitle();
	void previousSection();
	void nextSection();
	void setSection(int section);
	virtual void resetCurrentSection();

	void disableAutoSection();

	float getRange();
};