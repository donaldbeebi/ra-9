#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <queue>

enum class soundAction { play, stop };

struct SoundRequest {
	std::string sound;
	bool hasPosition;
	sf::Vector2f position;
	soundAction action;

	SoundRequest(std::string sound, soundAction action) {
		this->sound = sound;
		hasPosition = false;
		position = sf::Vector2f(0.0f, 0.0f);
		this->action = action;
	}

	SoundRequest(std::string sound, sf::Vector2f position) {
		this->sound = sound;
		hasPosition = true;
		this->position = position;
		action = soundAction::play;
	}
};

class SoundComponent {
private:
	std::queue<SoundRequest> m_Requests;
	bool m_HasPosition;
	sf::Vector2f m_Position;

public:
	SoundComponent();
	SoundComponent(sf::Vector2f position);

	void play(std::string sound);
	void playPosition(std::string sound, sf::Vector2f position);
	void stop(std::string sound);

	bool requesting();
	SoundRequest getSoundRequest();
};