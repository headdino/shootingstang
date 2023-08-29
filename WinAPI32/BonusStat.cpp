#include "stdafx.h"
#include "BonusStat.h"


BonusStat::BonusStat()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_bullet, sizeof(m_bullet));
}


BonusStat::~BonusStat()
{
}

HRESULT BonusStat::init()
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

HRESULT BonusStat::init(FPOINT startpt, int type)
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
	case ATTSPD:
		m_floatNum = 0.05f;
		break;
	case DMG:
		m_intNum = 20;
		break;
	case MHP:
		m_intNum = 10;
		break;
	case MVSPD:
		m_floatNum = 40.0f;
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

HRESULT BonusStat::init(int startpt, int type)
{
	m_attackType = BASIC;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;

	m_itemType = type;

	switch (startpt)
	{
	case 0: m_monster.pt = PointMake(WINSIZEX + 100.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	case 1: m_monster.pt = PointMake(WINSIZEX - 100.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	case 2: m_monster.pt = PointMake(WINSIZEX - 200.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	case 3: m_monster.pt = PointMake(WINSIZEX - 300.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	case 4: m_monster.pt = PointMake(WINSIZEX - 400.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	case 5: m_monster.pt = PointMake(WINSIZEX - 500.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
		break;
	}
	
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 80.0f };

	switch (m_itemType)
	{
	case ATTSPD:
		m_floatNum = 0.05f;
		break;
	case DMG:
		m_intNum = 20;
		break;
	case MHP:
		m_intNum = 10;
		break;
	case MVSPD:
		m_floatNum = 40.0f;
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

void BonusStat::release()
{
}

void BonusStat::update()
{
	SwitchState();
	frameMove();

	if (m_monster.rc.right < -100) m_monsterState = M_DEAD;

	m_monster.rc = { m_monster.pt.x,m_monster.pt.y,
					m_monster.pt.x + 40.0f, m_monster.pt.y + 40.0f };

}

void BonusStat::render()
{
	//DrawfRect(g_MemDC, m_monster.rc);
	switch (m_itemType)
	{
	case ATTSPD:
		IMGMANAGER->render("Bonus_attSpd", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	case DMG:
		IMGMANAGER->render("Bonus_dmg", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	case MHP:
		IMGMANAGER->render("Bonus_mhp", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	case MVSPD:
		IMGMANAGER->render("Bonus_mvspd", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
		break;
	}

}

void BonusStat::frameMove()
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
