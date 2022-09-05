#pragma once
#include "StandardObject.h"

class Bed : public StandardObject {
public:
	Bed(std::string name, Vector2f initialCenterPosition);
};
