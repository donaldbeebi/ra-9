#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "AnimationComponent.h"
#include "LoopedAnimationComponent.h"
#include "PingpongAnimationComponent.h"
#include "Component.h"
#include "GraphicsComponent.h"
#include "CharacterGraphicsComponent.h"
#include "StaticGraphicsComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "InteractComponent.h"
#include "DialogueComponent.h"

using namespace sf;

class GameObject {
protected:
	bool m_HasTC;
	bool m_HasAC;
	bool m_HasGC;
	bool m_HasCC;
	bool m_HasIC;
	bool m_HasDC;

	std::shared_ptr<TransformComponent> m_TC;
	std::shared_ptr<ColliderComponent> m_CC;
	std::shared_ptr<InteractComponent> m_IC;
	std::shared_ptr<DialogueComponent> m_DC;

	std::string m_Tag;
	std::string m_Name;

public:
	GameObject(std::string name);
	
	bool hasTC();
	bool hasAC();
	bool hasGC();
	bool hasCC();
	bool hasIC();
	bool hasDC();

	void disableDC();
	
	std::shared_ptr<TransformComponent> getTC();
	virtual std::shared_ptr<GraphicsComponent> getGC() = 0;
	std::shared_ptr<ColliderComponent> getCC();
	virtual std::shared_ptr<AnimationComponent> getAC() = 0;
	virtual std::shared_ptr<InteractComponent> getIC() = 0;
	std::shared_ptr<DialogueComponent> getDC();

	std::string getTag();
	std::string getName();

	virtual void update(float dt) = 0;
	virtual void updateGC(float dt) = 0;
	virtual void draw(RenderWindow& window) = 0;
	void drawTC(RenderWindow& window);
};