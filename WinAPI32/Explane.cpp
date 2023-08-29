#include "stdafx.h"
#include "Explane.h"


Explane::Explane()
{
}


Explane::~Explane()
{
}

HRESULT Explane::init()
{
	m_MenuPT = PointMake(0.0f,400.0f);
	m_ExplanPT = PointMake(0.0f, 500.0f);

	m_MenuRC = RectMake(m_MenuPT.x, m_MenuPT.y, 200.0f, 100.0f);
	m_ExplanRC = RectMake(m_ExplanPT.x, m_ExplanPT.y, 200.0f, 100.0f);

	PlayFrame = 0;
	ExplaneFrame = 0;

	m_GameState = EXPLAN;

	m_isOne = true;

	return S_OK;
}

void Explane::release()
{

}

void Explane::update()
{
	if (PtInRect(m_MenuRC, g_ptMouse))
	{
		PlayFrame = 1;

		if (KEYMANAGER->isKeyDown(VK_LBUTTON))
		{
			m_GameState = MENU;
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
			if (m_isOne)
			{
				m_isOne = false;
			}
			else
			{
				m_isOne = true;
			}
		}
	}
	else
	{
		ExplaneFrame = 0;
	}



}

void Explane::render()
{
	IMGMANAGER->render("Sky3", g_MemDC);

	//DrawfRect(g_MemDC, m_PlayRC);
	//DrawfRect(g_MemDC, m_ExplanRC);
	IMGMANAGER->frameRender("GameStart", g_MemDC, PlayFrame, 0, m_MenuPT.x, m_MenuPT.y, 200, 100);
	IMGMANAGER->frameRender("Explane", g_MemDC, ExplaneFrame, 0, m_ExplanPT.x, m_ExplanPT.y, 200, 100);

	if (m_isOne)
	{
		IMGMANAGER->render("Explan_1", g_MemDC, 200.0f, 0.0f);
	}
	else
	{
		IMGMANAGER->render("Explan_2", g_MemDC, 200.0f, 0.0f);
	}
	
}
