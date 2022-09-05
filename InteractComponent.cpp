#include "InteractComponent.h"

InteractComponent::InteractComponent(std::string name, float tileRange, std::shared_ptr<PAnimationComponent> AC) {
	m_Name = name;
	m_PushAction = name + "_push";
	m_ReleaseAction = name + "_release";
	m_Range = tileRange * 64.0f;
	m_AC = AC;
	m_GC = nullptr;
	m_HasAC = true;
	m_HasDescription = false;
	m_InteractedWith = false;
	m_Triggered = false;
	m_ForcingInteract = false;;
}

InteractComponent::InteractComponent(std::string name, float tileRange, std::shared_ptr<GraphicsComponent> GC) {
	m_Name = name;
	m_PushAction = name + "_push";
	m_ReleaseAction = name + "_release";
	m_Range = tileRange * 64.0f;
	m_AC = nullptr;
	m_GC = GC;
	m_HasAC = false;
	m_HasDescription = false;
	m_InteractedWith = false;
	m_Triggered = false;
	m_ForcingInteract = false;
}

void InteractComponent::addDescription(std::string description) {
	m_Description.push_back(description);
	if (!m_HasDescription) m_HasDescription = true;
}

std::string InteractComponent::getAction() {
	if (m_HasAC) {
		if (m_AC->getState() == 1 && !m_Triggered) {
			m_InteractedWith = false;
			m_Triggered = true;
			playPush();
			return m_PushAction;
		}
		if (m_AC->getState() == 0 && m_Triggered) {
			m_InteractedWith = false;
			m_Triggered = false;
			playRelease();
			return m_ReleaseAction;
		}
	}
	else {
		if ((m_GC->getStateCount() > 1 && m_GC->getState() == 1 && !m_Triggered) || (m_GC->getStateCount() == 1 && m_InteractedWith && !m_Triggered)) {
			m_InteractedWith = false;
			m_Triggered = true;
			playPush();
			return m_PushAction;
		}
		if ((m_GC->getStateCount() > 1 && m_GC->getState() == 0 && m_Triggered) || (m_GC->getStateCount() == 1 && m_InteractedWith && m_Triggered)) {
			m_InteractedWith = false;
			m_Triggered = false;
			playRelease();
			return m_ReleaseAction;
		}
	}
	return "none";
}

bool InteractComponent::isTriggered() {
	return m_Triggered;
}

void InteractComponent::interact() {
	if (!m_ForcingInteract) {
		if (m_HasAC) {
			m_AC->play();
		}
		else if (!m_HasAC && m_GC->getStateCount() != 1) {
			m_GC->setState(1);
		}
		m_InteractedWith = true;
	}
}

void InteractComponent::release() {
	if (!m_ForcingInteract) {
		if (m_HasAC) {
			m_AC->reverse();
		}
		else if (!m_HasAC && m_GC->getStateCount() != 1) {
			m_GC->setState(0);
		}
		m_InteractedWith = true;
	}
}

void InteractComponent::forceInteract() {
	m_ForcingInteract = true;
}

float InteractComponent::getRange() {
	return m_Range;
}

void InteractComponent::update() {
	if (m_ForcingInteract) {
		if (!m_InteractedWith) {
			if (m_HasAC) {
				m_AC->play();
			}
			else if (!m_HasAC && m_GC->getStateCount() != 1) {
				m_GC->setState(1);
			}
			m_InteractedWith = true;
		}
		if (m_HasAC) {
			if (m_AC->getState() == 1) {
				m_AC->reverse();
				m_InteractedWith = false;
				m_ForcingInteract = false;
			}
		}
		else {
			if (m_GC->getState() == 1) {
				m_GC->setState(0);
				m_InteractedWith = false;
				m_ForcingInteract = false;
			}
		}
	}
}

void InteractComponent::playPush() {
	if (m_Name.find("lever") != std::string::npos) {
		SoundManager::play("switchpush");
	}
	else if (m_Name.find("number_button") != std::string::npos) {
		SoundManager::play("buttonpush");
	}
	else if (m_Name.find("bigbutton") != std::string::npos) {
		SoundManager::play("bigbuttonpush");
	}
}

void InteractComponent::playRelease() {
	if (m_Name.find("lever") != std::string::npos) {
		SoundManager::play("switchrelease");
	}
	else if (m_Name.find("number_button") != std::string::npos) {
		SoundManager::play("buttonrelease");
	}
	else if (m_Name.find("bigbutton") != std::string::npos) {
		SoundManager::play("bigbuttonrelease");
	}
}