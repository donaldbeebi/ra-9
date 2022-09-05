//TRIGGER COMPONENT IS LIKE INTERACT BUT PASSIVELY ACTIVATED
#pragma once
#include <memory>
#include "InteractComponent.h"
#include "TransformComponent.h"

class TriggerComponent {
private:
	std::string m_TriggerSound;
	std::string m_ReleaseSound;

public:
	TriggerComponent(std::shared_ptr<TransformComponent> TC);

	void update(std::shared_ptr<InteractComponent> IC);
};