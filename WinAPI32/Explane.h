#pragma once
#include "GameNode.h"

class Explane : public GameNode
{
private:
	FPOINT m_MenuPT;
	FPOINT m_ExplanPT;

	FRECT m_MenuRC;
	FRECT m_ExplanRC;

	int PlayFrame;
	int ExplaneFrame;

	GAME_STATE m_GameState;

	bool m_isOne;
public:
	Explane();
	~Explane() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	GAME_STATE GetGameState() { return m_GameState; }
	void SetGameState(GAME_STATE state) { m_GameState = state; }

};