#pragma once
#include "InteractiveObject.h"

class Key : public InteractiveObject {
public:
	Key(std::string name, Vector2f initialCenterPosition);
};