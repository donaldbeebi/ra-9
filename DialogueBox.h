//IMPLEMENT - dialogue without the speaker's name display
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Structs.h"
#include <sstream>
#include "SoundManager.h"

using namespace sf;

class DialogueBox {
private:
	Sprite m_Sprite;
	FloatRect m_PrintArea;

	Font m_Font;
	Text m_SpeakerText;
	Text m_Text;
	float m_TextSpeed;

	std::string m_StringToPrint;
	std::string m_CurrentString;
	int m_CurrentStringSize;
	int m_CurrentCharacter;

	bool m_IsPrinting;
	float m_PrintTime;
	float m_SlowPrintTime;
	float m_CurrentTime;
	bool m_InstantPrint;
	bool m_Interact;

	std::string m_Action;
	int m_ButtonGroup;

	int m_PortraitState;
	std::string m_CurrentSpeaker;
	bool m_PortraitEnabled;

public:
	DialogueBox(std::string texture, Vector2f intialCenterPosition);

	void play(DialogueLine dialogue);
	bool isPrinting();
	void skip();
	void reset();

	bool isPunctuationMark(char c);
	bool hasSound(char);

	void update(float dt);
	void draw(RenderWindow& window);

	int getPortraitState();
	std::string getCurrentSpeaker();

	void enablePortrait();

	//feedback
	std::string getAction();
};