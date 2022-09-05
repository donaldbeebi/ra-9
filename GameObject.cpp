#include "GameObject.h"

GameObject::GameObject(std::string name) {
	m_HasTC = false;
	m_HasAC = false;
	m_HasGC = false;
	m_HasCC = false;
	m_HasIC = false;
	m_HasDC = false;

	m_TC = nullptr;
	m_CC = nullptr;
	m_DC = nullptr;

	m_Tag = "";
	m_Name = name;
}

bool GameObject::hasTC() {
	return m_HasTC;
}

bool GameObject::hasAC() {
	return m_HasAC;
}

bool GameObject::hasGC() {
	return m_HasGC;
}

bool GameObject::hasCC() {
	return m_HasCC;
}

bool GameObject::hasIC() {
	return m_HasIC;
}

bool GameObject::hasDC() {
	return m_HasDC;
}

void GameObject::disableDC() {
	m_HasDC = false;
}

std::shared_ptr<TransformComponent> GameObject::getTC() {
	return m_TC;
}

std::shared_ptr<ColliderComponent> GameObject::getCC() {
	return m_CC;
}

std::shared_ptr<DialogueComponent> GameObject::getDC() {
	return m_DC;
}

std::string GameObject::getTag() {
	return m_Tag;
}

std::string GameObject::getName() {
	return m_Name;
}

void GameObject::drawTC(RenderWindow& window) {
	m_TC->draw(window);
}