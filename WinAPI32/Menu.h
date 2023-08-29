#pragma once
#include "GameNode.h"

class Menu : public GameNode
{
private:
	FPOINT m_PlayPT;
	FPOINT m_ExplanPT;

	FRECT m_PlayRC;
	FRECT m_ExplanRC;

	int PlayFrame;
	int ExplaneFrame;

	GAME_STATE m_GameState;
public:
	Menu();
	~Menu() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	GAME_STATE GetGameState() { return m_GameState; }
	void SetGameState(GAME_STATE state) { m_GameState = state; }

};

