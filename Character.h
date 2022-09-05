#pragma once
#include "GameObject.h"
#include "CharacterDialogueComponent.h"
#include "Enums.h"

class Character : public GameObject {
protected:
	std::shared_ptr<LAnimationComponent> m_AC;
	std::shared_ptr<CharacterGraphicsComponent> m_GC;

	float m_Speed;
	bool m_IsMoving;
	Direction m_CurrentDirection;
	Vector2f m_CurrentVelocity;
	Vector2f dtov(Direction direction);
	float m_DT;

public:
	Character(std::string name);

	void move(Direction direction);

	virtual std::shared_ptr<AnimationComponent> getAC() override;
	virtual std::shared_ptr<GraphicsComponent> getGC() override;
	virtual std::shared_ptr<InteractComponent> getIC() override;
	virtual void update(float dt) override;
	virtual void updateGC(float dt) override;
	virtual void draw(RenderWindow&) override;
};