#include "stdafx.h"
#include "bird.h"


bird::bird()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_bullet, sizeof(m_bullet));
}


bird::~bird()
{
}

HRESULT bird::init()
{
	m_attackType = BASIC;
	m_moveType = ONLYX;
	m_monsterState = M_MOVE;

	m_monster.pt = PointMake(WINSIZEX + 100.0f, GetFromFloatTo(200.0f, WINSIZEY - 200.0f));
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 80.0f };
	m_monster.damage = 10;
	m_monster.hp = 100;
	m_monster.moveSpeed = 120.0f;

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

void bird::release()
{
}

void bird::update()
{
	SwitchState();
	frameMove();


	if (m_monster.hp <= 0) m_monsterState = M_DEAD; //cout << m_monster.hp << endl;
	if(m_monster.rc.right < -100) m_monsterState = M_DEAD;

	//if (m_monsterState != M_DEAD)
	//{
	//	//m_monster.pt.x -= m_monster.moveSpeed * g_ETime;
	//}

	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 80.0f };
}

void bird::render()
{
	//충돌박스 렌더
	//DrawfRect(g_MemDC, m_monster.rc);
	switch (m_monsterState)
	{
	case M_MOVE:
		IMGMANAGER->frameRender("Monster", g_MemDC, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 100, 100);
		break;
	case M_HIT:
		IMGMANAGER->frameAlphaRender("Monster", g_MemDC, m_alpha, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 100, 100);
		break;
	case M_DEAD:
		IMGMANAGER->frameAlphaRender("Monster", g_MemDC, m_alpha, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 100, 100);
		break;
	}
}

void bird::frameMove()
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
		case M_HIT:
			m_frameY = 1;
			m_frameX = 0;

			m_alpha = GetInt(105) + 100;

			break;
		case M_DEAD:
			m_frameY = 1;
			if (m_frameX == 0)
			{
				m_frameX = 0;
			}
			else
			{
				m_frameX = 0;
			}
			if (m_alpha - 10 > 0)
			{
				m_alpha -= 10;
			}
			break;
		}

	}
	else
	{
		m_time += g_ETime;
	}
}

/*void bird::SwitchState()
{
	switch (m_monsterState)
	{
	case M_MOVE:
		break;
	case M_HIT:
		if (m_StateTime >= m_HitTime)
		{
			m_monsterState = M_MOVE;
			m_alpha = 255;
			m_StateTime = 0.0f;
		}
		else
		{
			m_StateTime += g_ETime;
		}
		break;
	case M_DEAD:
		if (m_alpha - 10 <= 0)
		{
		
			m_isDead = true;
			
		}
		break;
	}
}
*/

void bird::Dammaged(int damage)
{
	m_monster.hp -= damage;
	m_monsterState = M_HIT;
	
}
