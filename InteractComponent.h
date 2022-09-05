//load audio based on sounds
#pragma once
#include <memory>
#include <vector>
#include <SFML/Audio.hpp>
#include "Component.h"
#include "GraphicsComponent.h"
#include "PingpongAnimationComponent.h"
#include "SoundManager.h"

class InteractComponent : public Component {
private:
	std::string m_Name;
	std::string m_PushAction;
	std::string m_ReleaseAction;
	std::vector<std::string> m_Description;
	float m_Range;
	std::shared_ptr<PAnimationComponent> m_AC;
	std::shared_ptr<GraphicsComponent> m_GC;
	bool m_HasAC;
	bool m_HasDescription;
	bool m_InteractedWith;
	bool m_Triggered;
	bool m_ForcingInteract;
	
public:
	InteractComponent(std::string name, float tileRange, std::shared_ptr<PAnimationComponent> AC);
	InteractComponent(std::string name, float tileRange, std::shared_ptr<GraphicsComponent> GC);
	void addDescription(std::string description);

	std::string getAction();
	bool isTriggered();

	void interact();
	void release();
	void forceInteract();
	float getRange(); //unused

	void update();

	void playPush();
	void playRelease();
};