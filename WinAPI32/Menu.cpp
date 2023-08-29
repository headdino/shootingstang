#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

HRESULT Menu::init()
{
	m_PlayPT = PointMake(WINSIZEX / 2.0f - 200.0f, WINSIZEY - 400.0f);
	m_ExplanPT = PointMake(WINSIZEX / 2.0f - 200.0f,WINSIZEY - 200.0f);

	m_PlayRC = RectMake(m_PlayPT.x, m_PlayPT.y, 400.0f, 200.0f);
	m_ExplanRC = RectMake(m_ExplanPT.x, m_ExplanPT.y, 400.0f, 200.0f);

	PlayFrame = 0;
	ExplaneFrame = 0;

	m_GameState = MENU;

	return S_OK;
}

void Menu::release()
{

}

void Menu::update()
{
	if (PtInRect(m_PlayRC, g_ptMouse))
	{
		PlayFrame = 1;

		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_GameState = INGAME;
			SOUNDMANAGER->play("BGM", 0.8f);
		}
	}
	else
	{
		PlayFrame = 0;
	}

	if (PtInRect(m_ExplanRC, g_ptMouse))
	{
		ExplaneFrame = 1;
		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_GameState = EXPLAN;
		}
	}
	else
	{
		ExplaneFrame = 0;
	}



}

void Menu::render()
{
	IMGMANAGER->render("Sky2", g_MemDC);

	//DrawfRect(g_MemDC, m_PlayRC);
	//DrawfRect(g_MemDC, m_ExplanRC);
	IMGMANAGER->frameRender("GameStart", g_MemDC, PlayFrame, 0, m_PlayPT.x, m_PlayPT.y, 400, 200);
	IMGMANAGER->frameRender("Explane", g_MemDC, ExplaneFrame, 0, m_ExplanPT.x, m_ExplanPT.y, 400, 200);
}
