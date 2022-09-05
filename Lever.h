#pragma once
#include "InteractiveObject.h"

class Lever : public InteractiveObject {
public:
	Lever(std::string name, Vector2f initialCenterPosition);
};