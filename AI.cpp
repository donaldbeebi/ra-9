#include "AI.h"

AI::AI(std::string name, Vector2f initialCenterPosition, std::shared_ptr<GameState> gameState) : Character(name) {
	m_Tag = "ai";
	m_Speed = 400.0f;
	m_GameState = gameState;

	/************************
	******For Stick Game*****
	************************/
	m_Chat = std::make_shared<DialogueComponent>("RA 9_Chat", 0.0f, true);
	m_Chat->setCustomTitle("RA 9");
	m_ChatSection = 0;
	m_OldChatSection = 0;

	m_BigTC = std::make_shared<TransformComponent>(Vector2f(928.0f, 504.0f), Vector2f(1.0f, 1.0f));
	m_BigGC = std::make_shared<StaticGraphicsComponent>("bigAI", 8, m_BigTC);
	m_BigGC->disableDrawOffset();

	/************************
	********For Battle*******
	************************/
	m_FightTC = std::make_shared<TransformComponent>(Vector2f(960.0f, 400.0f), Vector2f(1.0f, 1.0f));
	m_FightGC = std::make_shared<StaticGraphicsComponent>("fightingAI", 3, m_FightTC);
	m_FightGC->disableDrawOffset();
	m_TrC = std::make_shared<TremblingComponent>(m_FightTC);
	m_FightChat = std::make_shared<DialogueComponent>("RA 9_FightChat", 0.0f, true);
	m_FightChat->setCustomTitle("RA 9");

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.6f, 0.4f));
	m_TC->setYDimension(2.0f);
	m_HasTC = true;

	/************************
	***Animation Component***
	************************/
	m_AC = std::make_shared<LAnimationComponent>(m_Tag, Vector2u(1, 1));
	m_AC->setConstantSwitchTime(0.1f);
	m_AC->play();
	m_HasAC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<CharacterGraphicsComponent>(m_AC, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;

	/************************
	***Dialogue Component****
	************************/
	auto temp = std::make_shared<CharacterDialogueComponent>(m_Name, 2.0f, true);
	m_DC = temp;
	m_HasDC = true;

	m_State = std::make_unique<AIState>(gameState, temp, m_FightChat);
}

void AI::updateBigGC() {
	if (m_GameState->AIKilled() || m_GameState->AISaved()) {
		m_BigGC->disable();
	}
	else if (m_GameState->AISpared()) {
		m_BigGC->setState(7);
	}
	else {
		if (m_OldChatSection != m_ChatSection) {
			m_OldChatSection = m_ChatSection;
			switch (m_OldChatSection) {
			case 15:
				m_BigGC->setState(1);
				break;
			case 23:
				m_BigGC->setState(3);
				break;
			case 8:
				m_BigGC->setState(4);
				break;
			case 10:
			case 12:
				m_BigGC->setState(5);
				break;
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 24:
				m_BigGC->setState(6);
			}
		}
	}
}

void AI::prepareForCyberSpace(std::shared_ptr<GameObject> player, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<PanelManager> PM) {
	m_State->prepareForCyberspace(player, tilemap, PM);
}

void AI::prepareForBattle(std::shared_ptr<PanelManager> battlePM) {
	m_State->prepareForBattle(battlePM);
}

void AI::update(float dt) {
	//Character::update(dt);
	m_TC->update(dt);
	m_State->update();	
}

void AI::updateStickGame(float dt) {
	m_BigTC->update(dt);
	m_BigGC->update(dt);
	updateBigGC();
}

void AI::updateBattle(float dt) {
	m_FightTC->update(dt);
	m_FightGC->update(dt);
	m_TrC->update(dt);
	m_State->update();
}

std::string AI::getAction() {
	return m_State->getAction();
}

int AI::removeSticksIfThereAre(int sticks) {
	return std::max(((sticks % 5) + 4) % 5, 1);
}

void AI::ifPlayerSaid(int chatSection) {
	m_ChatSection = chatSection;
	m_Chat->setSection(m_ChatSection);
}

void AI::saySomething() {
	m_Chat->trigger("inspect");
}

std::shared_ptr<DialogueComponent> AI::getChatComponent() {
	return m_Chat;
}

std::shared_ptr<StaticGraphicsComponent> AI::getBigGC() {
	return m_BigGC;
}

std::shared_ptr<TransformComponent> AI::getBigTC() {
	return m_BigTC;
}

std::shared_ptr<StaticGraphicsComponent> AI::getFightGC() {
	return m_FightGC;
}

std::shared_ptr<TransformComponent> AI::getFightTC() {
	return m_FightTC;
}

std::shared_ptr<TremblingComponent> AI::getTrC() {
	return m_TrC;
}

std::shared_ptr<DialogueComponent> AI::getFightChat() {
	return m_FightChat;
}