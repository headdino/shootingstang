#include "stdafx.h"
#include "PlayGame.h"


PlayGame::PlayGame()
		: m_loopX(NULL)
{
}


PlayGame::~PlayGame()
{
}

HRESULT PlayGame::init()
{
	m_stage = 0;
	m_pPlayer = new Player;
	m_pPlayer->init();

	m_pMonster = new MonsterManager;
	m_pMonster->init();
	m_pMonster->givePlayer(m_pPlayer);

	m_isWin = true;
	m_isOnGame = true;
	m_textY = 200.0f;

	return S_OK;
}

void PlayGame::release()
{
	m_pPlayer->release();
	SAFE_DELETE(m_pPlayer);

	m_pMonster->release();
	SAFE_DELETE(m_pMonster);
}

void PlayGame::update()
{
	if (m_isOnGame)
	{
		m_pPlayer->update();
		m_pMonster->update();
		m_loopX += 6;
		if (m_loopX > 5000)
		{
			m_loopX = 0;
			m_stage += 1;
			if (m_stage >= 3) m_stage = 0;
		}

		if (!m_pPlayer->GetOngame())
		{
			m_isOnGame = false;
			m_isWin = false;
		}
		if (!m_pMonster->GetOngame())
		{
			m_isOnGame = false;
			m_isWin = true;
		}
	}
	else
	{
		m_loopX++;
		m_loopY++;
		m_textY -= 0.3f;
	}
	

}

void PlayGame::render()
{
	if (m_isOnGame)
	{
		switch (m_stage)
		{
		case 0:	IMGMANAGER->loopRender("Sky1", g_MemDC, 0, 0, m_loopX, 0);
			break;
		case 1:IMGMANAGER->loopRender("Sky2", g_MemDC, 0, 0, m_loopX, 0);
			break;
		case 2:IMGMANAGER->loopRender("Sky3", g_MemDC, 0, 0, m_loopX, 0);
			break;
		}



		m_pMonster->render();
		m_pPlayer->render();
	}
	else
	{
		if (m_isWin)
		{
			//IMGMANAGER->loopRender("BackGround_win", g_MemDC, WINSIZEX, WINSIZEY, m_loopX, m_loopY);
			IMGMANAGER->loopRender("BackGround_win", g_MemDC, 0, 0, m_loopX, m_loopY);
			IMGMANAGER->render("Text_Win", g_MemDC, 400.0f, m_textY);
		}
		else
		{
			//IMGMANAGER->loopRender("BackGround_lose", g_MemDC, WINSIZEX, WINSIZEY, m_loopX, m_loopY);
			IMGMANAGER->loopRender("BackGround_lose", g_MemDC, 0, 0, m_loopX, m_loopY);
			IMGMANAGER->render("Text_lose", g_MemDC, 400.0f, 200.0f);
		}
	}
}
