#pragma once
#include "StandardObject.h"

class Guitar : public StandardObject {
public:
	Guitar(std::string name, Vector2f initialCenterPosition);
};
