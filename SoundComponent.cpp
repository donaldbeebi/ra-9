#include "SoundComponent.h"

SoundComponent::SoundComponent() {
	m_HasPosition = false;
	m_Position = sf::Vector2f(0.0f, 0.0f);
}

SoundComponent::SoundComponent(sf::Vector2f position) {
	m_HasPosition = true;
	m_Position = position;
}

void SoundComponent::play(std::string sound) {
	m_Requests.push(SoundRequest(sound, soundAction::play));
}

void SoundComponent::playPosition(std::string sound, sf::Vector2f position) {
	m_Requests.push(SoundRequest(sound, position));
}

void SoundComponent::stop(std::string sound) {
	m_Requests.push(SoundRequest(sound, soundAction::stop));
}

bool SoundComponent::requesting() {
	return !m_Requests.empty();
}

SoundRequest SoundComponent::getSoundRequest() {
	if (!m_Requests.empty()) {
		SoundRequest temp = m_Requests.front();
		m_Requests.pop();
		return temp;
	}
	else return SoundRequest("none", soundAction::play);
}