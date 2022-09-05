#pragma once
#include "InteractiveObject.h"

class NumberButton : public InteractiveObject {
public:
	NumberButton(std::string name, Vector2f initialCenterPosition);
};
