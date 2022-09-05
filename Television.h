#pragma once
#include "StandardObject.h"

class Television : public StandardObject {
public:
	Television(std::string name, Vector2f initialCenterPosition);
};
