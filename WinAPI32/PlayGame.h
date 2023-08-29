#pragma once
#include "GameNode.h"
#include "Player.h"
#include "MonsterManager.h"

class PlayGame : public GameNode
{
private:
	Player* m_pPlayer;
	MonsterManager* m_pMonster;

	UINT m_loopX;
	UINT m_loopY;
	UINT m_stage;

	float m_textY;

	bool m_isOnGame;
	bool m_isWin;
public:
	PlayGame();
	~PlayGame() override;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;


};

