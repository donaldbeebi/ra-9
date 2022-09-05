#pragma once
#include "Shaker.h"

class ScreenShaker : public Shaker {
private:
	Vector2f m_ScreenOriginalPosition;
public:
	ScreenShaker(View& view);
	void stop();
	virtual void update(float dt) override;
};