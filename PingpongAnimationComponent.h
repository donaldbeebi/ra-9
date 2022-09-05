#pragma once
#include "AnimationComponent.h"

class PAnimationComponent : public AnimationComponent {
private:
	bool m_Forward;
	int m_State;

public:
	PAnimationComponent(std::string texture, Vector2u imageCount);

	int getState();

	void play();
	void reverse();

	bool isForward();
	bool isPlaying();

	virtual void update(float dt) override;
};