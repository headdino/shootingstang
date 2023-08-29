#pragma once
#include "GameNode.h"
#include "RectA.h"
#include "Star.h"
#include "PlayGame.h"
#include "Menu.h"
#include "Explane.h"

class MainGame :public GameNode
{
private:
	RECT m_rc;
	RectA* m_pRect;
	Star* m_pStar;

	Menu* m_pMenu;
	PlayGame* m_pGame;
	Explane* m_pExplane;

	GAME_STATE m_gameState;
public:
	MainGame();
	~MainGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void addImage();

};

