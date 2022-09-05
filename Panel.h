#pragma once
#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Selector.h"
#include "Button.h"
#include "DialogueBox.h"
#include "Portrait.h"
#include "Shaker.h"

using namespace sf;

class Panel {
protected:
	Sprite m_Background;
	bool m_Hidden = true;
	std::string m_Action;
	bool m_AwaitingMenuResponse;
	std::string m_Command;
	bool m_Ready;

	//Components
	std::shared_ptr<std::vector<std::shared_ptr<Button>>> m_Buttons = nullptr;
	bool m_HasButtons;
	std::vector<std::vector<int>> m_ButtonGroups;

	std::shared_ptr<Selector> m_Selector = nullptr;
	bool m_HasSelector;

	std::shared_ptr<DialogueBox> m_DialogueBox = nullptr;
	bool m_HasDialogueBox;

	std::shared_ptr<Portrait> m_Portrait = nullptr;
	bool m_HasPortrait;

	std::shared_ptr<Shaker> m_Shaker = nullptr;
	bool m_HasShaker;


public:
	View m_View;
	Panel(std::string background, Vector2f centerPosition, Vector2f resolution);

	virtual void update(float dt);
	void draw(RenderWindow& window);
	void show();
	void hide();
	void close();
	bool isHidden();
	void switchButtonGroup(int group);
	void setCommand(std::string command);

	virtual void actSelector(std::string action) {}
	virtual void actDialogue(std::string action) {}
	std::string getAction();

	std::shared_ptr<std::vector<std::shared_ptr<Button>>> getButtons();
	std::shared_ptr<Selector> getSelector();
	std::shared_ptr<DialogueBox> getDialogueBox();
	std::shared_ptr<Shaker> getShaker();

	bool hasDialogueBox();
	bool hasShaker();
};