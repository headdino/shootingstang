#include "stdafx.h"
#include "Lazor.h"


Lazor::Lazor()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_bullet, sizeof(m_bullet));
}


Lazor::~Lazor()
{
}

HRESULT Lazor::init()
{
	m_attackType = BASIC;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;

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


HRESULT Lazor::init(FPOINT startpt)
{
	m_attackType = BASIC;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;

	m_monster.pt = PointMake(startpt.x, startpt.y);
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

void Lazor::release()
{
}

void Lazor::update()
{
	SwitchState();
	frameMove();

	if (m_monster.rc.right < -100) m_monsterState = M_DEAD;

	m_monster.rc = { m_monster.pt.x,m_monster.pt.y,
					m_monster.pt.x + 40.0f, m_monster.pt.y + 40.0f };

}

void Lazor::render()
{
	//DrawfRect(g_MemDC, m_monster.rc);
	IMGMANAGER->render("Have_Lazor", g_MemDC, m_monster.pt.x, m_monster.pt.y, 40, 40);
}

void Lazor::frameMove()
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
