#pragma once
#include "TransformComponent.h"
#include <memory>

class TremblingComponent {
private:
	std::shared_ptr<TransformComponent> m_TC;
	float m_CurrentTime;
	float m_WaitTime;
	float m_Movement;
	float m_CurrentMovement;
	float m_Reduction;
	bool m_Triggered;
	int m_Direction;
	int m_Stage;
public:
	TremblingComponent(std::shared_ptr<TransformComponent> TC);

	void trigger();
	void triggerBig();
	void update(float dt);
};