#pragma once
#include "DialogueComponent.h"

class StickGameDialogueComponent : public DialogueComponent {
private:

public:
	StickGameDialogueComponent();

	virtual void trigger(std::string action) {};
};