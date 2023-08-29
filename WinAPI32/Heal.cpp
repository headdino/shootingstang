#include "stdafx.h"
#include "Heal.h"


Heal::Heal()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_bullet, sizeof(m_bullet));
}


Heal::~Heal()
{
}

HRESULT Heal::init()
{
	m_attackType = BASIC;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;
	m_itemType = 1;

	m_monster.pt = PointMake(WINSIZEX + 100.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 80.0f };
	m_monster.damage = 15;
	m_monster.hp = 100;
	m_monster.moveSpeed = 80.0f;

	m_time = 0.0f;
	m_frameCount = 1.0f / 5;
	m_frameX = 0;
	m_frameY = 0;
	m_alpha = 255;

	m_StateTime = 0.0f;
	m_HitTime = 0.8f;
	m_isDead = false;

	return S_OK;
}

HRESULT Heal::init(FPOINT startpt, int type)
{
	m_attackType = BASIC;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;

	m_itemType = type;

	m_monster.pt = PointMake(startpt.x, startpt.y);
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 80.0f };

	switch (m_itemType)
	{
	case HEAL1: m_monster.damage = 15; //Èú·® 15
		break;
	case HEAL2: m_monster.damage = 50; //Èú·® 50
		break;
	}
	
	m_monster.hp = 100;
	m_monster.moveSpeed = 80.0f;

	m_time = 0.0f;
	m_frameCount = 1.0f / 5;
	m_frameX = 0;
	m_frameY = 0;
	m_alpha = 255;

	m_StateTime = 0.0f;
	m_HitTime = 0.8f;
	m_isDead = false;

	return S_OK;
}

void Heal::release()
{
}

void Heal::update()
{
	SwitchState();
	frameMove();

	if (m_monster.rc.right < -100) m_monsterState = M_DEAD;

	m_monster.rc = { m_monster.pt.x,m_monster.pt.y,
					m_monster.pt.x + 40.0f, m_monster.pt.y + 40.0f };

}

void Heal::render()
{
	//DrawfRect(g_MemDC, m_monster.rc);
	switch (m_itemType)
	{
	case HEAL1:
		IMGMANAGER->render("Heal1", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	case HEAL2:
		IMGMANAGER->render("Heal2", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	}
	
}

void Heal::frameMove()
{
	if (m_time > m_frameCount)
	{
		m_time -= m_frameCount;
		switch (m_monsterState)
		{
		case M_MOVE:
			m_frameY = 0;
			if (m_frameX >= 4)
			{
				m_frameX = 0;
			}
			else
			{
				m_frameX++;
			}
			break;
		}

	}
	else
	{
		m_time += g_ETime;
	}

}
