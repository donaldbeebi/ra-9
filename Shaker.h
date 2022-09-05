#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Shaker {
protected:
	View& m_View;
	float m_CurrentTime;
	float m_WaitTime;
	float m_ShakeAmount;
	float m_CurrentShakeAmount;
	float m_ShakeReductionAmount;
	int m_Stage;
	bool m_Triggered;
	int m_Direction;
	bool m_Started;

public:
	Shaker(View& view);
	void setAmount(float amount);
	void setWaitTime(float waitTime);
	void trigger();
	void start();
	void stop();
	virtual void update(float dt);
};