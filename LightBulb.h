#pragma once
#include "StandardObject.h"

class LightBulb : public StandardObject {
public:
	LightBulb(std::string name, Vector2f initialCenterPosition);
};