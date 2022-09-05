#pragma once
#include "Trigger.h"
#include "GameObject.h"
#include "Tilemap.h"

class LocationTrigger : public Trigger {
private:
	std::shared_ptr<GameObject> m_Player;
	FloatRect m_Area;
	std::shared_ptr<Tilemap> m_Tilemap;
	std::string m_Location;
	bool m_Setting;

public:
	//LocationTrigger(std::shared_ptr<GameObject> player, FloatRect area) {
	//	m_Player = player;
	//	m_Area = FloatRect(area.left * 64.0f, area.top * 64.0f, area.width * 64.0f, area.height * 64.0f);
	//	m_Setting = false;
	//}
	LocationTrigger(std::shared_ptr<Tilemap> tilemap, std::string targetLocation) {
		m_Tilemap = tilemap;
		m_Location = targetLocation;
		m_Setting = true;
	}

	virtual void update() {
		if (m_Active) {
			if (m_Setting == false) {
				bool isWithinX = m_Player->getTC()->getPosition().x > m_Area.left && m_Player->getTC()->getPosition().x < (m_Area.left + m_Area.width);
				bool isWithinY = m_Player->getTC()->getPosition().y > m_Area.top && m_Player->getTC()->getPosition().y < (m_Area.top + m_Area.height);
				if (isWithinX && isWithinY) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else {
				if (m_Tilemap->getCurrentLocation() == m_Location) {
					m_Triggered = true;
					m_Active = false;
				}
			}
		}
	}
};