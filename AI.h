#pragma once
#include "Character.h"
#include "Enums.h"
#include "GameState.h"
#include "AIState.h"
#include "PanelManager.h"
#include "TremblingComponent.h"

class AI : public Character {
private:
	std::unique_ptr<AIState> m_State;
	int m_ChatSection;
	int m_OldChatSection;
	std::shared_ptr<DialogueComponent> m_Chat;
	std::shared_ptr<GameObject> m_Player;
	std::shared_ptr<Tilemap> m_Tilemap;

	std::shared_ptr<TransformComponent> m_BigTC;
	std::shared_ptr<StaticGraphicsComponent> m_BigGC;

	std::shared_ptr<TransformComponent> m_FightTC;
	std::shared_ptr<StaticGraphicsComponent> m_FightGC;
	std::shared_ptr<TremblingComponent> m_TrC;
	std::shared_ptr<DialogueComponent> m_FightChat;
	std::shared_ptr<GameState> m_GameState;

	void updateBigGC();

public:
	AI(std::string name, Vector2f initialCenterPosition, std::shared_ptr<GameState> gameState);

	void prepareForCyberSpace(std::shared_ptr<GameObject> player, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<PanelManager> PM);
	void prepareForBattle(std::shared_ptr<PanelManager> battlePM);

	virtual void update(float dt) override;
	void updateStickGame(float dt);
	void updateBattle(float dt);
	std::string getAction();

	//responses
	int removeSticksIfThereAre(int sticks);
	void ifPlayerSaid(int chatSection);
	void saySomething();
	std::shared_ptr<DialogueComponent> getChatComponent();
	std::shared_ptr<TransformComponent> getBigTC();
	std::shared_ptr<StaticGraphicsComponent> getBigGC();

	std::shared_ptr<TransformComponent> getFightTC();
	std::shared_ptr<StaticGraphicsComponent> getFightGC();
	std::shared_ptr<TremblingComponent> getTrC();
	std::shared_ptr<DialogueComponent> getFightChat();
};