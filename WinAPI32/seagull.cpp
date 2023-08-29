#include "stdafx.h"
#include "seagull.h"

seagull::seagull()
{
	ZeroMemory(&m_monster, sizeof(m_monster));
	ZeroMemory(&m_bullet, sizeof(m_bullet));
}


seagull::~seagull()
{
}

HRESULT seagull::init()
{
	m_attackType = MOVE_BULLET;
	m_moveType = XANDY;
	m_monsterState = M_MOVE;

	m_monster.pt = PointMake(WINSIZEX + 100.0f, GetFromFloatTo(50.0f, WINSIZEY - 50.0f));
	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 90.0f };
	m_monster.damage = 40;
	m_monster.hp = 600;
	//m_monster.moveSpeed = 240.0f;
	m_monster.moveSpeed = 50.0f + GetFloat(100.0f);

	for (int i = 0; i < BULLETMAX; i++)
	{
		m_bullet[i].moveSpeed = 200.0f;
		m_bullet[i].isfire = false;
	}

	m_time = 0.0f;
	m_frameCount = 1.0f / 3;
	m_frameX = 0;
	m_frameY = 0;
	m_alpha = 255;

	m_StateTime = 0.0f;
	m_HitTime = 1.8f;
	m_isDead = false;

	m_canAttack = false;
	m_attackTime = 0.0f;
	m_attackDelay = 1.2f;

	return S_OK;
}

void seagull::release()
{
}

void seagull::update()
{
	SwitchState();
	frameMove();
	bulletMove();

	if (m_monster.hp <= 0) m_monsterState = M_DEAD;// cout << m_monster.hp << endl;
	if (m_monster.rc.right < -100) m_monsterState = M_DEAD;

	if (m_canAttack && m_monsterState != M_DEAD) attack();
	else
	{
		if (m_attackTime > m_attackDelay)
		{
			m_attackTime -= m_attackDelay;
			m_canAttack = true;
		}
		else
		{
			m_attackTime += g_ETime;
		}
	}

	m_monster.rc = { m_monster.pt.x,m_monster.pt.y + 20.0f,
					m_monster.pt.x + 90.0f, m_monster.pt.y + 90.0f };
}

void seagull::render()
{
	//충돌박스 렌더
	//DrawfRect(g_MemDC, m_monster.rc);
	switch (m_monsterState)
	{
	case M_MOVE:
		IMGMANAGER->frameRender("Monster3_move", g_MemDC, m_frameX, m_frameY,
			m_monster.pt.x, m_monster.pt.y, 100, 100);
		break;
	case M_HIT:
		IMGMANAGER->alphaRender("Monster3_hit", g_MemDC, m_alpha, m_monster.pt.x, m_monster.pt.y,
			100, 100);
		break;
	case M_DEAD:
		IMGMANAGER->alphaRender("Monster3_hit", g_MemDC, m_alpha, m_monster.pt.x, m_monster.pt.y,
			100, 100);
		break;
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (m_bullet[i].isfire)
		{
			//DrawfCircle(g_MemDC, m_bullet[i].cc);
			IMGMANAGER->rotateRender("Monster3_bullet", g_MemDC, m_bullet[i].imageRotateRadian, false,
				1.0f, m_bullet[i].pt.x - m_bullet[i].cc.r, m_bullet[i].pt.y - m_bullet[i].cc.r);
		}

	}
}

void seagull::frameMove()
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
			m_frameY = 0;
			if (m_frameX >= 1) m_frameX = 0;
			else m_frameX++;

			m_alpha = GetInt(105) + 100;

			break;
		case M_DEAD:
			m_frameY = 0;
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

void seagull::attack()
{
	m_canAttack = false;
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!m_bullet[i].isfire)
		{
			m_bullet[i].pt = PointMake(m_monster.rc.right,
				m_monster.rc.top + (m_monster.rc.bottom - m_monster.rc.top) / 2.0f);
			m_bullet[i].isfire = true;
			m_canAttack = false;
			SOUNDMANAGER->play("Wind", 0.2f);

			break;
		}
	}
}

void seagull::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{

		if (m_bullet[i].isfire)
		{
			m_bullet[i].pt.x -= m_bullet[i].moveSpeed * g_ETime;
			m_bullet[i].pt.y -= sinf(GetRadian(m_bullet[i].pt.x, m_bullet[i].pt.y, m_playerPT.x, m_playerPT.y)) * m_bullet[i].moveSpeed / 2.0f * g_ETime;
			m_bullet[i].cc = CircleMake(m_bullet[i].pt.x, m_bullet[i].pt.y, 15.0f);
			m_bullet[i].imageRotateRadian++;

			if (m_bullet[i].cc.x < 0)
			{
				m_bullet[i].isfire = false;
			}
		}
	}
}


void seagull::Dammaged(int damage)
{
	m_monster.hp -= damage;
	m_monsterState = M_HIT;

}

