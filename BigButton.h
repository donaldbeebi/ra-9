#pragma once
#include "InteractiveObject.h"

class BigButton : public InteractiveObject {
public:
	BigButton(std::string name, Vector2f initialCenterPosition);
};