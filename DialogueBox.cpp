#include "DialogueBox.h"

DialogueBox::DialogueBox(std::string texture, Vector2f initialCenterPosition) {
	Texture& temp = TextureManager::getTexture("graphics/panels/" + texture + "_box.png");
	m_Sprite.setTexture(temp);
	m_Sprite.setOrigin(temp.getSize().x / 2, temp.getSize().y / 2);
	m_Sprite.setPosition(initialCenterPosition);
	m_PrintArea = m_Sprite.getGlobalBounds();
	m_PrintArea.left += 45;
	m_PrintArea.top += 40;
	m_PrintArea.width -= 90;
	m_PrintArea.height -= 60;
	
	m_SpeakerText.setFont(m_Font);
	m_SpeakerText.setCharacterSize(34);
	m_SpeakerText.setFillColor(Color::Yellow);
	m_SpeakerText.setString("");
	m_SpeakerText.setPosition(m_PrintArea.left, m_PrintArea.top);

	m_Font.loadFromFile("fonts/default.ttf");
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(34);
	m_Text.setString("");
	m_Text.setPosition(m_PrintArea.left, m_PrintArea.top);
	m_Text.setLineSpacing(1.5);
	m_TextSpeed = 0.1f; 

	m_StringToPrint = "";
	m_CurrentString = "";
	m_CurrentStringSize = 0;
	m_CurrentCharacter = 0;

	m_IsPrinting = false;
	m_PrintTime = 0.05f;
	m_CurrentTime = 0.0f;
	m_InstantPrint = false;
	m_Interact = false;

	m_Action = "none";
	m_ButtonGroup = 0;

	m_PortraitState = 0;
	m_CurrentSpeaker = "none";
	m_PortraitEnabled = false;
}

void DialogueBox::play(DialogueLine dialogue) {
	if (dialogue.line == "[END]") {
		m_Action = "dialogue_end";
		m_Text.setString("");
		m_SpeakerText.setString("");
	}
	else if (dialogue.line == "[INTERACT]") {
		m_Interact = true;
		m_ButtonGroup = 1;
		m_Action = "get_interact_command_line";
	}
	else if (dialogue.line == "[ANOTHER INTERACT]") {
		m_Interact = true;
		m_ButtonGroup = 2;
		m_Action = "get_another_interact_command_line";
	}
	else if (dialogue.line == "[COMMAND]") {
		m_Action = "get_standard_command_line";
	}
	else if (!m_IsPrinting) {
		m_CurrentSpeaker = dialogue.speaker;
		if (dialogue.speaker != "none" && !m_Interact) {
			m_SpeakerText.setString(dialogue.speaker + ":");
			if (dialogue.speaker == "RA 9" && m_PortraitEnabled) {
				m_StringToPrint = "";
				std::stringstream line;
				std::string portraitState;
				line.seekg(std::ios::beg);
				line.str(dialogue.line);
				std::getline(line, portraitState, ';');
				m_PortraitState = std::stoi(portraitState);

				std::string stringToAdd;
				while (std::getline(line, stringToAdd)) {
					m_StringToPrint.append(stringToAdd);
					m_StringToPrint.append("\n");
				}

				m_StringToPrint = "\n" + m_StringToPrint;
			}
			else {
				m_StringToPrint = "\n" + dialogue.line;
			}
		}
		else {
			m_SpeakerText.setString("");
			if (dialogue.speaker == "RA 9" && m_PortraitEnabled) {
				m_StringToPrint = "";
				std::stringstream line;
				std::string portraitState;
				line.seekg(std::ios::beg);
				line.str(dialogue.line);
				std::getline(line, portraitState, ';');
				m_PortraitState = std::stoi(portraitState);

				std::string stringToAdd;
				while (std::getline(line, stringToAdd)) {
					m_StringToPrint.append(stringToAdd);
					m_StringToPrint.append("\n");
				}
			}
			else m_StringToPrint = dialogue.line;
		}
		m_CurrentStringSize = m_StringToPrint.size();
		m_Text.setString("");
		m_IsPrinting = true;
	}
}

void DialogueBox::skip() {
	if(m_IsPrinting){
		m_InstantPrint = true;
	}
}

void DialogueBox::reset() {
	m_IsPrinting = false;
	m_CurrentCharacter = 0;
	m_CurrentString = "";
	m_CurrentTime = 0.0f;
	m_Interact = false;
	m_Text.setString("");
}

bool DialogueBox::isPrinting() {
	return m_IsPrinting;
}

bool DialogueBox::isPunctuationMark(char c) {
	switch(c) {
	case ',':
	case '.':
	case '!':
	case '?':
		return true;
	default:
		return false;
	}
}

bool DialogueBox::hasSound(char c) {
	switch (c) {
	case ',':
	case '.':
	case '!':
	case '?':
	case ' ':
	case '\n':
	case '\t':
		return false;
	default:
		return true;
	}
}

void DialogueBox::update(float dt){
	if (m_IsPrinting) {
		if (!m_InstantPrint) {
			m_CurrentTime += dt;
			if (m_CurrentTime >= m_PrintTime) {
				m_CurrentTime -= m_PrintTime;
				if (isPunctuationMark(m_StringToPrint[m_CurrentCharacter])) m_CurrentTime -= 0.1f;
				else if (m_StringToPrint[m_CurrentCharacter] == ' ') m_CurrentTime = m_PrintTime;

				m_CurrentString = m_CurrentString + m_StringToPrint[m_CurrentCharacter];
				m_Text.setString(m_CurrentString);
				if (hasSound(m_StringToPrint[m_CurrentCharacter])) {
					SoundManager::play("blip");
				}

				if (m_CurrentCharacter == m_CurrentStringSize - 1) {
					m_IsPrinting = false;
					m_CurrentCharacter = 0;
					m_CurrentString = "";
					m_CurrentTime = 0.0f;
					if (m_Interact) {
						m_Action = "interact_menu_ready_" + std::to_string(m_ButtonGroup);
						m_Interact = false;
					}
				}
				else m_CurrentCharacter++;
			}
		}
		else {
			m_Text.setString(m_StringToPrint);
			m_IsPrinting = false;
			m_CurrentCharacter = 0;
			m_CurrentString = "";
			m_CurrentTime = 0.0f;
			m_InstantPrint = false;
			if (m_Interact) {
				m_Action = "interact_menu_ready_" + std::to_string(m_ButtonGroup);
				m_Interact = false;
			}
		}
	}
}

void DialogueBox::draw(RenderWindow& window) {
	window.draw(m_Sprite);
	window.draw(m_SpeakerText);
	window.draw(m_Text);
}

int DialogueBox::getPortraitState() {
	return m_PortraitState;
}

std::string DialogueBox::getCurrentSpeaker() {
	return m_CurrentSpeaker;
}

void DialogueBox::enablePortrait() {
	m_PortraitEnabled = true;
}

std::string DialogueBox::getAction() {
	if (m_Action != "none") {
		std::string temp = m_Action;
		m_Action = "none";
		return temp;
	}
	return "none";
}