#pragma once
#include "Panel.h"

class DialoguePanel : public Panel {
private:
	std::string m_CurrentSpeaker;
	int m_CurrentPortraitState;
	void updatePortrait();
	//bool m_IsReady;

public:
	DialoguePanel(Vector2f resolution);

	virtual void actSelector(std::string action) override;
	virtual void actDialogue(std::string action) override;

	virtual void update(float dt) override;
	//bool isReady();
};